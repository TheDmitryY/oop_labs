#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "project_management.h"

using namespace std;

int Project::total_projects_count_ = 0;

Project::Project()
    : title("Новий проєкт"),
      client_name("Невідомий замовник"),
      deadline_days(30),
      project_code_(0),
      project_id_(0),
      total_budget_(10000.0),
      spent_budget_(0.0),
      required_resources_count_(1),
      lead_worker_(),
      module_() {
  ++total_projects_count_;
  cout << "[Project] Створено проєкт (за замовчуванням): " << title
       << " (ID: " << project_id_ << ")\n";
}

Project::Project(int id, const string& proj_title, const string& client,
                 int days, double total_budget, double spent_budget,
                 int resources, const Worker& lead, int code,
                 const ProjectModule& module)
    : title(proj_title),
      client_name(client),
      deadline_days(days),
      project_code_(code),
      project_id_(id),
      total_budget_(total_budget),
      spent_budget_(spent_budget),
      required_resources_count_(resources),
      lead_worker_(lead),
      module_(module) {
  ++total_projects_count_;
  cout << "[Project] Створено проєкт (з параметрами): " << title
       << " (ID: " << project_id_ << ")\n";
}

Project::Project(int id, const string& proj_title, const string& client,
                 int days, double total_budget, double spent_budget,
                 int resources, const Worker& lead)
    : title(proj_title),
      client_name(client),
      deadline_days(days),
      project_code_(id),
      project_id_(id),
      total_budget_(total_budget),
      spent_budget_(spent_budget),
      required_resources_count_(resources),
      lead_worker_(lead),
      module_() {
  ++total_projects_count_;
  cout << "[Project] Створено проєкт (з параметрами): " << title
       << " (ID: " << project_id_ << ")\n";
}

Project::Project(const Project& other)
    : title(other.title),
      client_name(other.client_name),
      deadline_days(other.deadline_days),
      project_code_(other.project_code_),
      project_id_(other.project_id_),
      total_budget_(other.total_budget_),
      spent_budget_(other.spent_budget_),
      required_resources_count_(other.required_resources_count_),
      lead_worker_(other.lead_worker_),
      module_(other.module_) {
  ++total_projects_count_;
  cout << "[Project] Скопійовано проєкт (конструктор копіювання): " << title
       << " (ID: " << project_id_ << ")\n";
}

Project& Project::operator=(const Project& other) {
  if (this != &other) {
    title = other.title;
    client_name = other.client_name;
    deadline_days = other.deadline_days;
    project_id_ = other.project_id_;
    total_budget_ = other.total_budget_;
    spent_budget_ = other.spent_budget_;
    required_resources_count_ = other.required_resources_count_;
    lead_worker_ = other.lead_worker_;
    module_ = other.module_;
  }
  return *this;
}

Project::~Project() {
  --total_projects_count_;
  cout << "[Project] Знищено проєкт: " << title << " (ID: " << project_id_
       << ")\n";
}

double Project::GetRemainingBudget() const {
  return (total_budget_ > spent_budget_) ? (total_budget_ - spent_budget_)
                                         : 0.0;
}

void Project::AddResources(int count) {
  if (count > 0) {
    required_resources_count_ += count;
    cout << "[Project " << title << "] Додано " << count
         << " одиниць ресурсів. Всього: " << required_resources_count_ << "\n";
  }
}

void Project::AddResources(int count, double additional_cost) {
  if (count > 0) {
    required_resources_count_ += count;
    spent_budget_ += additional_cost;
    cout << "[Project " << title << "] Додано " << count
         << " одиниць ресурсів вартістю " << additional_cost
         << " грн. Витрачено бюджету: " << spent_budget_ << " грн.\n";
  }
}

bool Project::AssignBudgetToLead(double amount) {
  if (amount <= 0) return false;
  if (amount > GetRemainingBudget()) {
    cout << "[Project " << title << "] Недостатньо бюджету для виділення "
         << amount << " грн! Залишок: " << GetRemainingBudget() << " грн.\n";
    return false;
  }
  spent_budget_ += amount;
  lead_worker_.AllocateBudget(amount);
  cout << "[Project " << title << "] Виділено " << amount << " грн керівнику "
       << lead_worker_.name
       << ". Залишок бюджету проєкту: " << GetRemainingBudget() << " грн.\n";
  return true;
}

void Project::MergeProject(const Project& other) {
  this->title += " + " + other.title;
  this->total_budget_ += other.total_budget_;
  this->spent_budget_ += other.spent_budget_;
  this->deadline_days = max(this->deadline_days, other.deadline_days);
  this->required_resources_count_ += other.required_resources_count_;
  cout << "[Об'єднання проєктів] Об'єднано з проєктом #" << other.project_id_
       << " ('" << other.title << "'). Новий бюджет: " << this->total_budget_
       << " грн, дедлайн: " << this->deadline_days << " днів.\n";
}

Project Project::CreateSubproject(const string& sub_title,
                                  double sub_budget) const {
  double actual_budget =
      (sub_budget <= GetRemainingBudget()) ? sub_budget : GetRemainingBudget();
  Project subproject(this->project_id_ * 10 + 1, sub_title, this->client_name,
                     this->deadline_days / 2, actual_budget, 0.0, 2,
                     this->lead_worker_, this->project_code_ * 10 + 1,
                     this->module_);
  cout << "[Створення підпроєкту] Створено новий підпроєкт '" << sub_title
       << "' з бюджетом " << actual_budget << " грн.\n";
  return subproject;
}

bool Project::ExecuteSprint(int tasks_to_complete, double sprint_cost) {
  cout << "\n>>> Старт спринту для проєкту '" << title << "' <<<\n";
  cout << "Замовник: " << client_name
       << " | Відповідальний: " << lead_worker_.name << " ("
       << lead_worker_.position << ")\n";
  if (sprint_cost > GetRemainingBudget()) {
    cout << "ПОМИЛКА: Недостатньо коштів на спринт! Потрібно: " << sprint_cost
         << ", доступно: " << GetRemainingBudget() << "\n";
    return false;
  }

  spent_budget_ += sprint_cost;
  lead_worker_.AllocateBudget(sprint_cost);
  lead_worker_.CompleteTasks(tasks_to_complete, sprint_cost);
  deadline_days = max(0, deadline_days - 14);

  cout << "Спринт успішно завершено! Залишок бюджету проєкту: "
       << GetRemainingBudget() << " грн, днів до дедлайну: " << deadline_days
       << "\n";
  return true;
}

void Project::DeliverCurrentModule(int progress) {
  cout << "[Project " << title
       << "] Передача завдання вбудованому модулю за композицією...\n";
  module_.Execute(progress);
  double spent_for_module = module_.GetAllocatedFunds() * (progress / 100.0);
  spent_budget_ += spent_for_module;
  cout << "[Project " << title << "] Модуль частково реалізовано на "
       << progress << "%. Списано з бюджету проєкту: " << spent_for_module
       << " грн.\n";
}

bool Project::SaveToFile(const string& filename) const {
  ofstream out(filename);
  if (!out.is_open()) {
    cerr << "Помилка відкриття файлу для запису проєкту: " << filename << "\n";
    return false;
  }
  WriteToStream(out);
  out.close();
  return true;
}

void Project::WriteToStream(ostream& out) const {
  out << project_id_ << "\n";
  out << title << "\n";
  out << client_name << "\n";
  out << deadline_days << "\n";
  out << total_budget_ << "\n";
  out << spent_budget_ << "\n";
  out << required_resources_count_ << "\n";
  lead_worker_.WriteToStream(out);
}

bool Project::LoadFromFile(const string& filename) {
  ifstream in(filename);
  if (!in.is_open()) {
    cerr << "Помилка відкриття файлу для читання проєкту: " << filename << "\n";
    return false;
  }
  bool result = ReadFromStream(in);
  in.close();
  return result;
}

bool Project::ReadFromStream(istream& in) {
  if (!(in >> project_id_)) return false;
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  if (!getline(in, title)) return false;
  if (!getline(in, client_name)) return false;
  if (!(in >> deadline_days)) return false;
  if (!(in >> total_budget_)) return false;
  if (!(in >> spent_budget_)) return false;
  if (!(in >> required_resources_count_)) return false;
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  return lead_worker_.ReadFromStream(in);
}

void Project::AllocateAndSortMemory() const {
  int size = (rand() % 8) + 5;
  int* dynamic_array = new int[size];

  for (int i = 0; i < size; ++i) {
    int deviation = (rand() % 21) - 10;
    dynamic_array[i] = max(1, deadline_days + deviation);
  }

  cout << "\n[Project::AllocateAndSortMemory] Виділено " << size
       << " елементів у динамічній пам'яті на основі deadline_days ("
       << deadline_days << "):\n  Початкові значення: ";
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

void Project::PrintTotalProjectsCount() {
  cout << "[Project::PrintTotalProjectsCount] Загальна кількість створених "
          "проєктів у системі: "
       << total_projects_count_ << "\n";
}

void Project::PrintInfo() const {
  cout << "========================================\n"
       << "Проєкт #" << project_id_ << ": \"" << title << "\"\n"
       << "Код проєкту (const):     " << project_code_ << "\n"
       << "Замовник:                " << client_name << "\n"
       << "Термін (дедлайн):        " << deadline_days << " днів\n"
       << "Загальний бюджет:        " << fixed << setprecision(2)
       << total_budget_ << " грн\n"
       << "Витрачений бюджет:       " << spent_budget_ << " грн\n"
       << "Залишок бюджету:         " << GetRemainingBudget() << " грн\n"
       << "Необхідні ресурси:       " << required_resources_count_ << " од.\n"
       << "Керівник (Worker):       " << lead_worker_.name << " ("
       << lead_worker_.position << ")\n";
  module_.PrintInfo();
  cout << "========================================\n";
}
