#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "project_management.h"

using namespace std;

const string Worker::kDefaultDepartment = "Загальний відділ";
int Worker::total_workers_count_ = 0;

Worker::Worker()
    : name("Невідомо"),
      position("Стажер"),
      experience_years(0),
      access_level_(1),
      base_allowance_(1000.0),
      clearance_status_("Standard"),
      employee_code_(0),
      department_ref_(kDefaultDepartment),
      worker_id_(0),
      hourly_rate_(15.0),
      completed_tasks_(0),
      allocated_budget_(0.0),
      productivity_score_(70) {
  ++total_workers_count_;
  cout << "[Worker] Створено робітника (за замовчуванням): " << name
       << " (ID: " << worker_id_ << ")\n";
}

Worker::Worker(int id, const string& worker_name, const string& worker_position,
               int exp_years, double rate, int tasks, double budget,
               int productivity, int code, const string& dept)
    : name(worker_name),
      position(worker_position),
      experience_years(exp_years),
      access_level_(2),
      base_allowance_(2500.0),
      clearance_status_("Verified"),
      employee_code_(code),
      department_ref_(dept),
      worker_id_(id),
      hourly_rate_(rate),
      completed_tasks_(tasks),
      allocated_budget_(budget),
      productivity_score_(productivity) {
  ++total_workers_count_;
  cout << "[Worker] Створено робітника (з параметрами): " << name
       << " (ID: " << worker_id_ << ")\n";
}

Worker::Worker(int id, const string& worker_name, const string& worker_position,
               int exp_years, double rate, int tasks, double budget,
               int productivity)
    : name(worker_name),
      position(worker_position),
      experience_years(exp_years),
      access_level_(2),
      base_allowance_(2000.0),
      clearance_status_("Verified"),
      employee_code_(id),
      department_ref_(kDefaultDepartment),
      worker_id_(id),
      hourly_rate_(rate),
      completed_tasks_(tasks),
      allocated_budget_(budget),
      productivity_score_(productivity) {
  ++total_workers_count_;
  cout << "[Worker] Створено робітника (з параметрами): " << name
       << " (ID: " << worker_id_ << ")\n";
}

Worker::Worker(int id, const string& worker_name, const string& worker_position,
               int exp_years, double rate)
    : name(worker_name),
      position(worker_position),
      experience_years(exp_years),
      access_level_(1),
      base_allowance_(1500.0),
      clearance_status_("Standard"),
      employee_code_(id),
      department_ref_(kDefaultDepartment),
      worker_id_(id),
      hourly_rate_(rate),
      completed_tasks_(0),
      allocated_budget_(0.0),
      productivity_score_(75) {
  ++total_workers_count_;
  cout << "[Worker] Створено робітника (з 5 параметрами): " << name
       << " (ID: " << worker_id_ << ")\n";
}

Worker::Worker(const string& worker_name)
    : name(worker_name),
      position("Спеціаліст"),
      experience_years(1),
      access_level_(1),
      base_allowance_(1200.0),
      clearance_status_("Standard"),
      employee_code_(0),
      department_ref_(kDefaultDepartment),
      worker_id_(total_workers_count_ + 100),
      hourly_rate_(20.0),
      completed_tasks_(0),
      allocated_budget_(0.0),
      productivity_score_(75) {
  ++total_workers_count_;
  cout << "[Worker] Створено робітника (скорочений спосіб): " << name
       << " (ID: " << worker_id_ << ")\n";
}

Worker::Worker(const Worker& other)
    : name(other.name),
      position(other.position),
      experience_years(other.experience_years),
      access_level_(other.access_level_),
      base_allowance_(other.base_allowance_),
      clearance_status_(other.clearance_status_),
      employee_code_(other.employee_code_),
      department_ref_(other.department_ref_),
      worker_id_(other.worker_id_),
      hourly_rate_(other.hourly_rate_),
      completed_tasks_(other.completed_tasks_),
      allocated_budget_(other.allocated_budget_),
      productivity_score_(other.productivity_score_) {
  ++total_workers_count_;
  cout << "[Worker] Скопійовано робітника (конструктор копіювання): " << name
       << " (ID: " << worker_id_ << ")\n";
}

Worker& Worker::operator=(const Worker& other) {
  if (this != &other) {
    name = other.name;
    position = other.position;
    experience_years = other.experience_years;
    access_level_ = other.access_level_;
    base_allowance_ = other.base_allowance_;
    clearance_status_ = other.clearance_status_;
    worker_id_ = other.worker_id_;
    hourly_rate_ = other.hourly_rate_;
    completed_tasks_ = other.completed_tasks_;
    allocated_budget_ = other.allocated_budget_;
    productivity_score_ = other.productivity_score_;
  }
  return *this;
}

Worker::~Worker() {
  --total_workers_count_;
  cout << "[Worker] Знищено робітника: " << name << " (ID: " << worker_id_
       << ")\n";
}

double Worker::CalculateSalary(int hours_worked) const {
  if (hours_worked <= 0) return 0.0;
  double base_pay = hours_worked * hourly_rate_;
  double productivity_factor = productivity_score_ / 100.0;
  double experience_bonus = (experience_years > 5) ? 1.15 : 1.0;
  return base_pay * productivity_factor * experience_bonus;
}

void Worker::CompleteTasks() {
  completed_tasks_++;
  if (productivity_score_ < 100) {
    productivity_score_++;
  }
  cout << "[Worker " << name
       << "] Виконано 1 завдання. Всього завдань: " << completed_tasks_
       << ", поточна продуктивність: " << productivity_score_ << "%\n";
}

void Worker::CompleteTasks(int tasks_count, double budget_spent) {
  if (tasks_count <= 0) return;
  completed_tasks_ += tasks_count;
  if (allocated_budget_ >= budget_spent) {
    allocated_budget_ -= budget_spent;
  } else {
    allocated_budget_ = 0.0;
  }
  productivity_score_ = min(100, productivity_score_ + tasks_count);
  cout << "[Worker " << name << "] Виконано " << tasks_count
       << " завдань, витрачено бюджету: " << budget_spent
       << " грн. Залишок виділеного бюджету: " << allocated_budget_
       << " грн.\n";
}

void Worker::AllocateBudget(double amount) {
  if (amount > 0) {
    allocated_budget_ += amount;
    cout << "[Worker " << name << "] Додано бюджет у розмірі " << amount
         << " грн. Загальний виділений бюджет: " << allocated_budget_
         << " грн.\n";
  }
}

bool Worker::CompareExperience(const Worker& other) const {
  int score_this = this->experience_years * 10 + this->completed_tasks_;
  int score_other = other.experience_years * 10 + other.completed_tasks_;
  cout << "[Порівняння] " << this->name << " (бал досвіду: " << score_this
       << ") vs " << other.name << " (бал досвіду: " << score_other << ")\n";
  return score_this >= score_other;
}

Worker Worker::CreatePromotedWorker(const string& new_position,
                                    double bonus_rate) const {
  Worker promoted = *this;
  promoted.position = new_position;
  promoted.experience_years += 1;
  promoted.hourly_rate_ += bonus_rate;
  promoted.productivity_score_ = min(100, promoted.productivity_score_ + 5);
  cout << "[Підвищення] Створено новий об'єкт Worker для " << promoted.name
       << " з посадою: " << promoted.position
       << ", нова ставка: " << promoted.hourly_rate_ << " $/год\n";
  return promoted;
}

bool Worker::SaveToFile(const string& filename) const {
  ofstream out(filename);
  if (!out.is_open()) {
    cerr << "Помилка відкриття файлу для запису: " << filename << "\n";
    return false;
  }
  WriteToStream(out);
  out.close();
  return true;
}

void Worker::WriteToStream(ostream& out) const {
  out << worker_id_ << "\n";
  out << name << "\n";
  out << position << "\n";
  out << experience_years << "\n";
  out << hourly_rate_ << "\n";
  out << completed_tasks_ << "\n";
  out << allocated_budget_ << "\n";
  out << productivity_score_ << "\n";
}

bool Worker::LoadFromFile(const string& filename) {
  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Помилка відкриття файлу для читання: " << filename << "\n";
    return false;
  }
  bool result = ReadFromStream(in);
  in.close();
  return result;
}

bool Worker::ReadFromStream(istream& in) {
  if (!(in >> worker_id_)) return false;
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  if (!getline(in, name)) return false;
  if (!getline(in, position)) return false;
  if (!(in >> experience_years)) return false;
  if (!(in >> hourly_rate_)) return false;
  if (!(in >> completed_tasks_)) return false;
  if (!(in >> allocated_budget_)) return false;
  if (!(in >> productivity_score_)) return false;
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  return true;
}

void Worker::AllocateAndSortMemory() const {
  int size = (rand() % 8) + 5;
  int* dynamic_array = new int[size];

  for (int i = 0; i < size; ++i) {
    int deviation = (rand() % 31) - 15;
    dynamic_array[i] = max(0, min(100, productivity_score_ + deviation));
  }

  cout << "\n[Worker::AllocateAndSortMemory] Виділено " << size
       << " елементів у динамічній пам'яті на основі productivity_score_ ("
       << productivity_score_ << "):\n  Початкові значення: ";
  for (int i = 0; i < size; ++i) {
    cout << dynamic_array[i] << " ";
  }
  cout << "\n";

  sort(dynamic_array, dynamic_array + size);

  cout << "  Відсортовані значення: ";
  for (int i = 0; i < size; ++i) {
    cout << dynamic_array[i] << " ";
  }
  cout << "\n";

  delete[] dynamic_array;
}

void Worker::PrintTotalWorkersCount() {
  cout << "[Worker::PrintTotalWorkersCount] Загальна кількість створених "
          "робітників у системі: "
       << total_workers_count_ << "\n";
}

void Worker::PrintInfo() const {
  cout << "=== Робітник #" << worker_id_ << " ===\n"
       << "  Код робітника (const):  " << employee_code_ << "\n"
       << "  Відділ (посилання):     " << department_ref_ << "\n"
       << "  Ім'я:                   " << name << "\n"
       << "  Посада:                 " << position << "\n"
       << "  Досвід (років):         " << experience_years << "\n"
       << "  Погодинна ставка:       " << hourly_rate_ << " $/год\n"
       << "  Виконано завдань:       " << completed_tasks_ << "\n"
       << "  Виділений бюджет:       " << allocated_budget_ << " грн\n"
       << "  Оцінка продуктивності:  " << productivity_score_ << "%\n"
       << "  Рівень допуску:         " << access_level_ << "\n"
       << "  Статус перевірки:       " << clearance_status_ << "\n";
}

void Worker::PublicWorkReport() const {
  cout << "[Worker::PublicWorkReport] Робітник " << name << " (" << position
       << "): статус перевірки: " << clearance_status_
       << ", виконано завдань: " << completed_tasks_ << "\n";
}

void Worker::ProtectedSecurityCheck() const {
  cout << "[Worker::ProtectedSecurityCheck] [Захищений метод] Рівень допуску: "
       << access_level_ << ", статус безпеки: " << clearance_status_ << "\n";
}

double Worker::CalculateInternalBonus(double factor) const {
  double bonus = base_allowance_ * factor * (experience_years > 3 ? 1.2 : 1.0);
  cout << "[Worker::CalculateInternalBonus] [Захищений метод] Внутрішній бонус: "
       << bonus << " грн (коефіцієнт: " << factor << ")\n";
  return bonus;
}

void Worker::UpdateClearance(int new_level, const string& status) {
  access_level_ = new_level;
  clearance_status_ = status;
  cout << "[Worker::UpdateClearance] [Захищений метод] Оновлено рівень допуску "
       << name << " -> рівень " << access_level_ << " (" << clearance_status_ << ")\n";
}

void Worker::PrivateAuditLog(const string& action) const {
  cout << "[Worker::PrivateAuditLog] [Приватний метод] Дія '" << action
       << "' зафіксована для працівника ID " << worker_id_ << "\n";
}

bool Worker::ValidateConfidentialCredentials() const {
  return (employee_code_ > 0 && worker_id_ > 0);
}

double Worker::ComputeTaxDeductions(double amount) const {
  return amount * 0.195;
}


void CalculateWorkerEfficiency(Worker worker) {
  double salary = worker.CalculateSalary(160);
  double budget = worker.GetAllocatedBudget();
  int tasks = worker.GetCompletedTasks();
  int score = worker.GetProductivityScore();
  double efficiency =
      (tasks > 0) ? ((salary + budget) / tasks) : (salary + budget);
  cout << "\n[CalculateWorkerEfficiency (за значенням)]\n"
       << "Робітник: " << worker.name << "\n"
       << "Зарплата (160 год): " << salary << " $\n"
       << "Виділений бюджет: " << budget << " грн\n"
       << "Виконано завдань: " << tasks << "\n"
       << "Продуктивність: " << score << "%\n"
       << "Фінансові витрати на одиницю завдання: " << efficiency << "\n";
}

void CalculateWorkerEfficiency(const Worker* worker) {
  if (!worker) {
    cout << "\n[CalculateWorkerEfficiency (за адресою)] Помилка: покажчик "
            "nullptr!\n";
    return;
  }
  double salary = worker->CalculateSalary(160);
  double budget = worker->GetAllocatedBudget();
  int tasks = worker->GetCompletedTasks();
  int score = worker->GetProductivityScore();
  double efficiency =
      (tasks > 0) ? ((salary + budget) / tasks) : (salary + budget);
  cout << "\n[CalculateWorkerEfficiency (за адресою / покажчиком)]\n"
       << "Адреса об'єкта: " << worker << "\n"
       << "Робітник: " << worker->name << "\n"
       << "Зарплата (160 год): " << salary << " $\n"
       << "Виділений бюджет: " << budget << " грн\n"
       << "Виконано завдань: " << tasks << "\n"
       << "Продуктивність: " << score << "%\n"
       << "Фінансові витрати на одиницю завдання: " << efficiency << "\n";
}

Worker ProcessWorkerBonusAndElevation(Worker worker, double extra_budget,
                                      int extra_tasks) {
  cout << "\n[ProcessWorkerBonusAndElevation] Преміювання робітника "
       << worker.name << "\n";
  worker.AllocateBudget(extra_budget);
  worker.CompleteTasks(extra_tasks, extra_budget * 0.5);
  worker.SetProductivityScore(min(100, worker.GetProductivityScore() + 8));
  return worker;
}
