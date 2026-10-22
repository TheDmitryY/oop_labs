#include "personnel_system.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

PersonnelException::PersonnelException(const std::string& message)
    : std::runtime_error(message) {}
ValidationException::ValidationException(const std::string& message)
    : PersonnelException(message) {}
DuplicateIdException::DuplicateIdException(const std::string& message)
    : PersonnelException(message) {}
CapacityException::CapacityException(const std::string& message)
    : PersonnelException(message) {}
RecordNotFoundException::RecordNotFoundException(const std::string& message)
    : PersonnelException(message) {}
FileException::FileException(const std::string& message)
    : PersonnelException(message) {}

Employee::Employee(int id, const std::string& name, double salary)
    : id_(id), name_(name), salary_(salary) {
  ValidateBaseData();
}

Employee::~Employee() = default;
int Employee::GetId() const { return id_; }
const std::string& Employee::GetName() const { return name_; }
double Employee::GetSalary() const { return salary_; }
void Employee::SetSalary(double salary) {
  salary_ = salary;
  ValidateBaseData();
}

void Employee::Print(std::ostream& out) const {
  out << "ID: " << id_ << ", ім'я: " << name_ << ", зарплата: " << salary_;
}

void Employee::Write(std::ostream& out) const {
  out << id_ << '\n' << name_ << '\n' << salary_ << '\n';
}

void Employee::Read(std::istream& in) {
  if (!(in >> id_)) throw FileException("Некоректний ідентифікатор у файлі");
  in.ignore();
  if (!std::getline(in, name_) || !(in >> salary_)) {
    throw FileException("Не вдалося прочитати базові дані працівника");
  }
  in.ignore();
  ValidateBaseData();
}

void Employee::PrintShort(std::ostream& out) const {
  out << '[' << GetType() << "] " << GetName() << " (#" << GetId() << ')';
}

void Employee::ValidateBaseData() const {
  if (id_ <= 0 || name_.empty() || salary_ < 0) {
    throw ValidationException("ID має бути додатним, ім'я непорожнім, а зарплата невід'ємною");
  }
}

Developer::Developer(int id, const std::string& name, double salary,
                     const std::string& language, int completed_features)
    : Employee(id, name, salary), language_(language), completed_features_(completed_features) {
  if (language_.empty() || completed_features_ < 0) throw ValidationException("Некоректні дані розробника");
}
std::string Developer::GetType() const { return "Developer"; }
void Developer::Work() const { std::cout << GetName() << " реалізує функції мовою " << language_ << ".\n"; }
void Developer::Print(std::ostream& out) const { Employee::Print(out); out << ", мова: " << language_ << ", функцій: " << completed_features_; }
void Developer::Write(std::ostream& out) const { Employee::Write(out); out << language_ << '\n' << completed_features_ << '\n'; }
void Developer::Read(std::istream& in) { Employee::Read(in); if (!std::getline(in, language_) || !(in >> completed_features_)) throw FileException("Не вдалося прочитати дані розробника"); in.ignore(); if (language_.empty() || completed_features_ < 0) throw ValidationException("Некоректні дані розробника у файлі"); }
std::unique_ptr<Employee> Developer::Clone() const { return std::make_unique<Developer>(*this); }

Tester::Tester(int id, const std::string& name, double salary,
               const std::string& testing_tool, int found_bugs)
    : Employee(id, name, salary), testing_tool_(testing_tool), found_bugs_(found_bugs) {
  if (testing_tool_.empty() || found_bugs_ < 0) throw ValidationException("Некоректні дані тестувальника");
}
std::string Tester::GetType() const { return "Tester"; }
void Tester::Work() const { std::cout << GetName() << " тестує систему в " << testing_tool_ << ".\n"; }
void Tester::Print(std::ostream& out) const { Employee::Print(out); out << ", інструмент: " << testing_tool_ << ", багів: " << found_bugs_; }
void Tester::Write(std::ostream& out) const { Employee::Write(out); out << testing_tool_ << '\n' << found_bugs_ << '\n'; }
void Tester::Read(std::istream& in) { Employee::Read(in); if (!std::getline(in, testing_tool_) || !(in >> found_bugs_)) throw FileException("Не вдалося прочитати дані тестувальника"); in.ignore(); if (testing_tool_.empty() || found_bugs_ < 0) throw ValidationException("Некоректні дані тестувальника у файлі"); }
std::unique_ptr<Employee> Tester::Clone() const { return std::make_unique<Tester>(*this); }

Manager::Manager(int id, const std::string& name, double salary,
                 const std::string& department, int team_size)
    : Employee(id, name, salary), department_(department), team_size_(team_size) {
  if (department_.empty() || team_size_ < 0) throw ValidationException("Некоректні дані менеджера");
}
std::string Manager::GetType() const { return "Manager"; }
void Manager::Work() const { std::cout << GetName() << " координує відділ " << department_ << ".\n"; }
void Manager::Print(std::ostream& out) const { Employee::Print(out); out << ", відділ: " << department_ << ", команда: " << team_size_; }
void Manager::Write(std::ostream& out) const { Employee::Write(out); out << department_ << '\n' << team_size_ << '\n'; }
void Manager::Read(std::istream& in) { Employee::Read(in); if (!std::getline(in, department_) || !(in >> team_size_)) throw FileException("Не вдалося прочитати дані менеджера"); in.ignore(); if (department_.empty() || team_size_ < 0) throw ValidationException("Некоректні дані менеджера у файлі"); }
std::unique_ptr<Employee> Manager::Clone() const { return std::make_unique<Manager>(*this); }

namespace {
std::unique_ptr<Employee> ReadOne(std::istream& in) {
  std::string type;
  if (!std::getline(in, type)) throw FileException("Не вдалося прочитати тип працівника");
  std::unique_ptr<Employee> employee;
  if (type == "Developer") employee = std::make_unique<Developer>(1, "temp", 0, "temp", 0);
  else if (type == "Tester") employee = std::make_unique<Tester>(1, "temp", 0, "temp", 0);
  else if (type == "Manager") employee = std::make_unique<Manager>(1, "temp", 0, "temp", 0);
  else throw FileException("Невідомий тип працівника у файлі: " + type);
  employee->Read(in);
  return employee;
}

void WriteCollection(const std::vector<const Employee*>& records, const std::string& filename) {
  std::ofstream out(filename);
  if (!out) throw FileException("Не вдалося відкрити файл для запису: " + filename);
  out << records.size() << '\n';
  for (const Employee* employee : records) { out << employee->GetType() << '\n'; employee->Write(out); }
}
}

void ServiceStatic::Add(std::unique_ptr<Employee> employee) {
  if (!employee) throw ValidationException("Неможливо додати порожній об'єкт");
  if (size_ == kCapacity) throw CapacityException("Статичне сховище заповнене");
  if (ContainsId(employee->GetId())) throw DuplicateIdException("Працівник з таким ID уже існує");
  employees_[size_++] = std::move(employee);
}
void ServiceStatic::RemoveById(int id) { for (std::size_t i = 0; i < size_; ++i) if (employees_[i]->GetId() == id) { for (std::size_t j = i + 1; j < size_; ++j) employees_[j - 1] = std::move(employees_[j]); employees_[--size_].reset(); return; } throw RecordNotFoundException("Працівника для видалення не знайдено"); }
void ServiceStatic::PrintAll(std::ostream& out) const { out << "Статичне сховище: " << size_ << '/' << kCapacity << "\n"; for (std::size_t i = 0; i < size_; ++i) { employees_[i]->Print(out); out << '\n'; } }
void ServiceStatic::Write(const Employee& employee, const std::string& filename) const { std::ofstream out(filename); if (!out) throw FileException("Не вдалося відкрити файл: " + filename); out << employee.GetType() << '\n'; employee.Write(out); }
void ServiceStatic::Read(Employee& employee, const std::string& filename) const { std::ifstream in(filename); if (!in) throw FileException("Не вдалося відкрити файл: " + filename); std::string type; std::getline(in, type); if (type != employee.GetType()) throw FileException("Тип об'єкта не відповідає даним файлу"); employee.Read(in); }
void ServiceStatic::SaveAll(const std::string& filename) const { std::vector<const Employee*> records; for (std::size_t i = 0; i < size_; ++i) records.push_back(employees_[i].get()); WriteCollection(records, filename); }
void ServiceStatic::LoadAll(const std::string& filename) { std::ifstream in(filename); if (!in) throw FileException("Не вдалося відкрити файл: " + filename); std::size_t count; if (!(in >> count) || count > kCapacity) throw FileException("Некоректна кількість записів у файлі"); in.ignore(); std::array<std::unique_ptr<Employee>, kCapacity> loaded; for (std::size_t i = 0; i < count; ++i) { loaded[i] = ReadOne(in); for (std::size_t j = 0; j < i; ++j) if (loaded[j]->GetId() == loaded[i]->GetId()) throw DuplicateIdException("Повторюваний ID у файлі"); } employees_ = std::move(loaded); size_ = count; }
std::size_t ServiceStatic::Size() const { return size_; }
const Employee& ServiceStatic::At(std::size_t index) const { if (index >= size_) throw RecordNotFoundException("Індекс поза межами статичного сховища"); return *employees_[index]; }
bool ServiceStatic::ContainsId(int id) const { for (std::size_t i = 0; i < size_; ++i) if (employees_[i]->GetId() == id) return true; return false; }

void ServiceDynamic::Add(std::unique_ptr<Employee> employee) { if (!employee) throw ValidationException("Неможливо додати порожній об'єкт"); if (ContainsId(employee->GetId())) throw DuplicateIdException("Працівник з таким ID уже існує"); employees_.push_back(std::move(employee)); }
void ServiceDynamic::RemoveById(int id) { auto it = std::find_if(employees_.begin(), employees_.end(), [id](const std::unique_ptr<Employee>& employee) { return employee->GetId() == id; }); if (it == employees_.end()) throw RecordNotFoundException("Працівника для видалення не знайдено"); employees_.erase(it); }
void ServiceDynamic::PrintAll(std::ostream& out) const { out << "Динамічне сховище: " << employees_.size() << "\n"; for (const auto& employee : employees_) { employee->Print(out); out << '\n'; } }
void ServiceDynamic::Write(const Employee& employee, const std::string& filename) const { ServiceStatic().Write(employee, filename); }
void ServiceDynamic::Read(Employee& employee, const std::string& filename) const { ServiceStatic().Read(employee, filename); }
void ServiceDynamic::SaveAll(const std::string& filename) const { std::vector<const Employee*> records; for (const auto& employee : employees_) records.push_back(employee.get()); WriteCollection(records, filename); }
void ServiceDynamic::LoadAll(const std::string& filename) { std::ifstream in(filename); if (!in) throw FileException("Не вдалося відкрити файл: " + filename); std::size_t count; if (!(in >> count)) throw FileException("Некоректна кількість записів у файлі"); in.ignore(); std::vector<std::unique_ptr<Employee>> loaded; for (std::size_t i = 0; i < count; ++i) { auto employee = ReadOne(in); for (const auto& present : loaded) if (present->GetId() == employee->GetId()) throw DuplicateIdException("Повторюваний ID у файлі"); loaded.push_back(std::move(employee)); } employees_ = std::move(loaded); }
std::size_t ServiceDynamic::Size() const { return employees_.size(); }
const Employee& ServiceDynamic::At(std::size_t index) const { if (index >= employees_.size()) throw RecordNotFoundException("Індекс поза межами динамічного сховища"); return *employees_[index]; }
bool ServiceDynamic::ContainsId(int id) const { return std::any_of(employees_.begin(), employees_.end(), [id](const std::unique_ptr<Employee>& employee) { return employee->GetId() == id; }); }

std::unique_ptr<Employee> CreateEmployee(const std::string& type, int id, const std::string& name, double salary, const std::string& detail, int metric) { if (type == "1") return std::make_unique<Developer>(id, name, salary, detail, metric); if (type == "2") return std::make_unique<Tester>(id, name, salary, detail, metric); if (type == "3") return std::make_unique<Manager>(id, name, salary, detail, metric); throw ValidationException("Тип має бути 1, 2 або 3"); }

void DemonstratePolymorphism(const Employee& employee) { std::cout << "Поліморфізм через посилання: "; employee.Work(); const Employee* pointer = &employee; std::cout << "Поліморфізм через вказівник: "; pointer->Work(); std::vector<std::reference_wrapper<const Employee>> records{employee}; std::cout << "Поліморфізм через контейнер посилань: "; records.front().get().Work(); std::cout << "Раннє зв'язування: "; employee.PrintShort(std::cout); std::cout << "\nПізнє зв'язування: "; employee.Print(std::cout); std::cout << "\nОбхід віртуального виклику Employee::Print: "; employee.Employee::Print(std::cout); std::cout << "\n"; }

void DemonstrateExceptions() { std::cout << "Демонстрація п'яти виняткових ситуацій:\n"; try { Developer invalid(0, "", -1, "", -1); } catch (const ValidationException& error) { std::cout << "1. " << error.what() << '\n'; } try { ServiceStatic service; service.Add(std::make_unique<Developer>(1, "A", 1, "C++", 0)); service.Add(std::make_unique<Developer>(1, "B", 1, "C++", 0)); } catch (const DuplicateIdException& error) { std::cout << "2. " << error.what() << '\n'; } try { ServiceStatic service; for (int i = 0; i <= 10; ++i) service.Add(std::make_unique<Tester>(i + 1, "T", 1, "Qt", 0)); } catch (const CapacityException& error) { std::cout << "3. " << error.what() << '\n'; } try { ServiceDynamic service; service.RemoveById(99); } catch (const RecordNotFoundException& error) { std::cout << "4. " << error.what() << '\n'; } try { ServiceDynamic service; service.LoadAll("missing_personnel_file.txt"); } catch (const FileException& error) { std::cout << "5. " << error.what() << '\n'; } }
