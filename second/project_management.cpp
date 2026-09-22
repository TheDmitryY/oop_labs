// Copyright 2026 Dmitriy Mankevych
// Пункт 14: Дотримання правил Google C++ Style Guide
// Пункт 15: Файл 2 з 3 - cpp-файл із реалізацією класів

#include "project_management.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// ============================================================================
// Реалізація методів класу Worker (Пункт 1, Пункт 2)
// ============================================================================

Worker::Worker()
    : name("Невідомо"),
      position("Стажер"),
      experience_years(0),
      worker_id_(0),
      hourly_rate_(15.0),
      completed_tasks_(0),
      allocated_budget_(0.0),
      productivity_score_(70) {}

Worker::Worker(int id, const std::string& worker_name,
               const std::string& worker_position, int exp_years, double rate,
               int tasks, double budget, int productivity)
    : name(worker_name),
      position(worker_position),
      experience_years(exp_years),
      worker_id_(id),
      hourly_rate_(rate),
      completed_tasks_(tasks),
      allocated_budget_(budget),
      productivity_score_(productivity) {}

// Пункт 4 (Метод 1): Обчислення заробітної плати
// Використовує поля: hourly_rate_, productivity_score_, experience_years,
// position
double Worker::CalculateSalary(int hours_worked) const {
  if (hours_worked <= 0) return 0.0;
  double base_pay = hours_worked * hourly_rate_;
  double productivity_factor = productivity_score_ / 100.0;
  double experience_bonus = (experience_years > 5) ? 1.15 : 1.0;
  return base_pay * productivity_factor * experience_bonus;
}

// Пункт 4 (Метод 2 - перевантаження 1): Виконання одного стандартного завдання
// Використовує поля: completed_tasks_, productivity_score_
void Worker::CompleteTasks() {
  completed_tasks_++;
  if (productivity_score_ < 100) {
    productivity_score_++;
  }
  std::cout << "[Worker " << name
            << "] Виконано 1 завдання. Всього завдань: " << completed_tasks_
            << ", поточна продуктивність: " << productivity_score_ << "%\n";
}

// Пункт 4 (Метод 3 - перевантаження 2): Виконання кількох завдань із витратою
// бюджету Використовує поля: completed_tasks_, allocated_budget_,
// productivity_score_
void Worker::CompleteTasks(int tasks_count, double budget_spent) {
  if (tasks_count <= 0) return;
  completed_tasks_ += tasks_count;
  if (allocated_budget_ >= budget_spent) {
    allocated_budget_ -= budget_spent;
  } else {
    allocated_budget_ = 0.0;
  }
  productivity_score_ = std::min(100, productivity_score_ + tasks_count);
  std::cout << "[Worker " << name << "] Виконано " << tasks_count
            << " завдань, витрачено бюджету: " << budget_spent
            << " грн. Залишок виділеного бюджету: " << allocated_budget_
            << " грн.\n";
}

// Пункт 4 (Метод 4): Виділення бюджету робітнику на завдання
// Використовує поле: allocated_budget_
void Worker::AllocateBudget(double amount) {
  if (amount > 0) {
    allocated_budget_ += amount;
    std::cout << "[Worker " << name << "] Додано бюджет у розмірі " << amount
              << " грн. Загальний виділений бюджет: " << allocated_budget_
              << " грн.\n";
  }
}

// Пункт 4 (Метод 5): Метод приймає об'єкт класу Worker як параметр
// Порівнює сукупний досвід та виконання завдань між двома робітниками
bool Worker::CompareExperience(const Worker& other) const {
  int score_this = this->experience_years * 10 + this->completed_tasks_;
  int score_other = other.experience_years * 10 + other.completed_tasks_;
  std::cout << "[Порівняння] " << this->name << " (бал досвіду: " << score_this
            << ") vs " << other.name << " (бал досвіду: " << score_other
            << ")\n";
  return score_this >= score_other;
}

// Пункт 4 (Метод 6): Метод повертає тип класу Worker
// Створює новий об'єкт класу Worker з підвищеною посадою та збільшеною ставкою
Worker Worker::CreatePromotedWorker(const std::string& new_position,
                                    double bonus_rate) const {
  Worker promoted = *this;
  promoted.position = new_position;
  promoted.experience_years += 1;
  promoted.hourly_rate_ += bonus_rate;
  promoted.productivity_score_ =
      std::min(100, promoted.productivity_score_ + 5);
  std::cout << "[Підвищення] Створено новий об'єкт Worker для " << promoted.name
            << " з посадою: " << promoted.position
            << ", нова ставка: " << promoted.hourly_rate_ << " $/год\n";
  return promoted;
}

// Пункт 5: Запис у файл полів даних робітника
bool Worker::SaveToFile(const std::string& filename) const {
  std::ofstream out(filename);
  if (!out.is_open()) {
    std::cerr << "Помилка відкриття файлу для запису: " << filename << "\n";
    return false;
  }
  WriteToStream(out);
  out.close();
  return true;
}

void Worker::WriteToStream(std::ostream& out) const {
  out << worker_id_ << "\n";
  out << name << "\n";
  out << position << "\n";
  out << experience_years << "\n";
  out << hourly_rate_ << "\n";
  out << completed_tasks_ << "\n";
  out << allocated_budget_ << "\n";
  out << productivity_score_ << "\n";
}

// Пункт 5: Читання з файлу полів даних робітника
bool Worker::LoadFromFile(const std::string& filename) {
  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Помилка відкриття файлу для читання: " << filename << "\n";
    return false;
  }
  bool result = ReadFromStream(in);
  in.close();
  return result;
}

bool Worker::ReadFromStream(std::istream& in) {
  if (!(in >> worker_id_)) return false;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (!std::getline(in, name)) return false;
  if (!std::getline(in, position)) return false;
  if (!(in >> experience_years)) return false;
  if (!(in >> hourly_rate_)) return false;
  if (!(in >> completed_tasks_)) return false;
  if (!(in >> allocated_budget_)) return false;
  if (!(in >> productivity_score_)) return false;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return true;
}

// Пункт 12: Виділення випадкової величини динамічної пам'яті,
// розміщення множини значень одного з цілочисельних полів (productivity_score_)
// та їх сортування
void Worker::AllocateAndSortMemory() const {
  // Випадковий розмір масиву від 5 до 12
  int size = (std::rand() % 8) + 5;
  int* dynamic_array = new int[size];

  // Заповнюємо множиною значень на базі productivity_score_
  for (int i = 0; i < size; ++i) {
    int deviation = (std::rand() % 31) - 15;
    dynamic_array[i] =
        std::max(0, std::min(100, productivity_score_ + deviation));
  }

  std::cout << "\n[Worker::AllocateAndSortMemory] Виділено " << size
            << " елементів у динамічній пам'яті на основі productivity_score_ ("
            << productivity_score_ << "):\n  Початкові значення: ";
  for (int i = 0; i < size; ++i) {
    std::cout << dynamic_array[i] << " ";
  }
  std::cout << "\n";

  // Сортування значень у динамічній пам'яті
  std::sort(dynamic_array, dynamic_array + size);

  std::cout << "  Відсортовані значення: ";
  for (int i = 0; i < size; ++i) {
    std::cout << dynamic_array[i] << " ";
  }
  std::cout << "\n";

  // Звільнення динамічної пам'яті
  delete[] dynamic_array;
}

void Worker::PrintInfo() const {
  std::cout << "=== Робітник #" << worker_id_ << " ===\n"
            << "  Ім'я:                   " << name << "\n"
            << "  Посада:                 " << position << "\n"
            << "  Досвід (років):         " << experience_years << "\n"
            << "  Погодинна ставка:       " << hourly_rate_ << " $/год\n"
            << "  Виконано завдань:       " << completed_tasks_ << "\n"
            << "  Виділений бюджет:       " << allocated_budget_ << " грн\n"
            << "  Оцінка продуктивності:  " << productivity_score_ << "%\n";
}

// ============================================================================
// Реалізація методів класу Project (Пункт 1, Пункт 2, Пункт 3)
// ============================================================================

Project::Project()
    : title("Новий проєкт"),
      client_name("Невідомий замовник"),
      deadline_days(30),
      project_id_(0),
      total_budget_(10000.0),
      spent_budget_(0.0),
      required_resources_count_(1),
      lead_worker_() {}

Project::Project(int id, const std::string& proj_title,
                 const std::string& client, int days, double total_budget,
                 double spent_budget, int resources, const Worker& lead)
    : title(proj_title),
      client_name(client),
      deadline_days(days),
      project_id_(id),
      total_budget_(total_budget),
      spent_budget_(spent_budget),
      required_resources_count_(resources),
      lead_worker_(lead) {}

// Пункт 4 (Метод 1): Отримання залишку бюджету
// Використовує поля: total_budget_, spent_budget_
double Project::GetRemainingBudget() const {
  return (total_budget_ > spent_budget_) ? (total_budget_ - spent_budget_)
                                         : 0.0;
}

// Пункт 4 (Метод 2 - перевантаження 1): Додавання необхідних ресурсів
// Використовує поле: required_resources_count_
void Project::AddResources(int count) {
  if (count > 0) {
    required_resources_count_ += count;
    std::cout << "[Project " << title << "] Додано " << count
              << " одиниць ресурсів. Всього: " << required_resources_count_
              << "\n";
  }
}

// Пункт 4 (Метод 3 - перевантаження 2): Додавання ресурсів із витратами
// Використовує поля: required_resources_count_, spent_budget_
void Project::AddResources(int count, double additional_cost) {
  if (count > 0) {
    required_resources_count_ += count;
    spent_budget_ += additional_cost;
    std::cout << "[Project " << title << "] Додано " << count
              << " одиниць ресурсів вартістю " << additional_cost
              << " грн. Витрачено бюджету: " << spent_budget_ << " грн.\n";
  }
}

// Пункт 4 (Метод 4): Виділення бюджету проєкту відповідальному робітнику
// Використовує поля: total_budget_, spent_budget_, lead_worker_
bool Project::AssignBudgetToLead(double amount) {
  if (amount <= 0) return false;
  if (amount > GetRemainingBudget()) {
    std::cout << "[Project " << title << "] Недостатньо бюджету для виділення "
              << amount << " грн! Залишок: " << GetRemainingBudget()
              << " грн.\n";
    return false;
  }
  spent_budget_ += amount;
  lead_worker_.AllocateBudget(amount);
  std::cout << "[Project " << title << "] Виділено " << amount
            << " грн керівнику " << lead_worker_.name
            << ". Залишок бюджету проєкту: " << GetRemainingBudget()
            << " грн.\n";
  return true;
}

// Пункт 4 (Метод 5): Метод приймає об'єкт класу Project як параметр
// Об'єднує два проєкти в один спільний
void Project::MergeProject(const Project& other) {
  this->title += " + " + other.title;
  this->total_budget_ += other.total_budget_;
  this->spent_budget_ += other.spent_budget_;
  this->deadline_days = std::max(this->deadline_days, other.deadline_days);
  this->required_resources_count_ += other.required_resources_count_;
  std::cout << "[Об'єднання проєктів] Об'єднано з проєктом #"
            << other.project_id_ << " ('" << other.title
            << "'). Новий бюджет: " << this->total_budget_
            << " грн, дедлайн: " << this->deadline_days << " днів.\n";
}

// Пункт 4 (Метод 6): Метод повертає тип класу Project
// Створює підпроєкт на базі поточного проєкту
Project Project::CreateSubproject(const std::string& sub_title,
                                  double sub_budget) const {
  double actual_budget =
      (sub_budget <= GetRemainingBudget()) ? sub_budget : GetRemainingBudget();
  Project subproject(this->project_id_ * 10 + 1, sub_title, this->client_name,
                     this->deadline_days / 2, actual_budget, 0.0, 2,
                     this->lead_worker_);
  std::cout << "[Створення підпроєкту] Створено новий підпроєкт '" << sub_title
            << "' з бюджетом " << actual_budget << " грн.\n";
  return subproject;
}

// Пункт 10: Сценарій взаємодії двох об'єктів (Project і Worker)
// Керівник проєкту бере завдання, використовує бюджет проєкту, завершує
// завдання
bool Project::ExecuteSprint(int tasks_to_complete, double sprint_cost) {
  std::cout << "\n>>> Старт спринту для проєкту '" << title << "' <<<\n";
  std::cout << "Замовник: " << client_name
            << " | Відповідальний: " << lead_worker_.name << " ("
            << lead_worker_.position << ")\n";
  if (sprint_cost > GetRemainingBudget()) {
    std::cout << "ПОМИЛКА: Недостатньо коштів на спринт! Потрібно: "
              << sprint_cost << ", доступно: " << GetRemainingBudget() << "\n";
    return false;
  }

  // Виділяємо кошти робітнику на спринт
  spent_budget_ += sprint_cost;
  lead_worker_.AllocateBudget(sprint_cost);

  // Робітник виконує завдання, витрачаючи виділені кошти
  lead_worker_.CompleteTasks(tasks_to_complete, sprint_cost);

  // Витрата часу дедлайну
  deadline_days = std::max(0, deadline_days - 14);

  std::cout << "Спринт успішно завершено! Залишок бюджету проєкту: "
            << GetRemainingBudget()
            << " грн, днів до дедлайну: " << deadline_days << "\n";
  return true;
}

// Пункт 5: Запис у файл полів даних проєкту
bool Project::SaveToFile(const std::string& filename) const {
  std::ofstream out(filename);
  if (!out.is_open()) {
    std::cerr << "Помилка відкриття файлу для запису проєкту: " << filename
              << "\n";
    return false;
  }
  WriteToStream(out);
  out.close();
  return true;
}

void Project::WriteToStream(std::ostream& out) const {
  out << project_id_ << "\n";
  out << title << "\n";
  out << client_name << "\n";
  out << deadline_days << "\n";
  out << total_budget_ << "\n";
  out << spent_budget_ << "\n";
  out << required_resources_count_ << "\n";
  // Запис вкладеного об'єкта Worker (Пункт 3)
  lead_worker_.WriteToStream(out);
}

// Пункт 5: Читання з файлу полів даних проєкту
bool Project::LoadFromFile(const std::string& filename) {
  std::ifstream in(filename);
  if (!in.is_open()) {
    std::cerr << "Помилка відкриття файлу для читання проєкту: " << filename
              << "\n";
    return false;
  }
  bool result = ReadFromStream(in);
  in.close();
  return result;
}

bool Project::ReadFromStream(std::istream& in) {
  if (!(in >> project_id_)) return false;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  if (!std::getline(in, title)) return false;
  if (!std::getline(in, client_name)) return false;
  if (!(in >> deadline_days)) return false;
  if (!(in >> total_budget_)) return false;
  if (!(in >> spent_budget_)) return false;
  if (!(in >> required_resources_count_)) return false;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // Зчитування вкладеного об'єкта Worker (Пункт 3)
  return lead_worker_.ReadFromStream(in);
}

// Пункт 12: Виділення випадкової величини динамічної пам'яті,
// розміщення множини значень цілочисельного поля (deadline_days)
// та їх сортування
void Project::AllocateAndSortMemory() const {
  // Випадковий розмір масиву від 5 до 12
  int size = (std::rand() % 8) + 5;
  int* dynamic_array = new int[size];

  // Заповнюємо множиною значень на базі deadline_days
  for (int i = 0; i < size; ++i) {
    int deviation = (std::rand() % 21) - 10;
    dynamic_array[i] = std::max(1, deadline_days + deviation);
  }

  std::cout << "\n[Project::AllocateAndSortMemory] Виділено " << size
            << " елементів у динамічній пам'яті на основі deadline_days ("
            << deadline_days << "):\n  Початкові значення: ";
  for (int i = 0; i < size; ++i) {
    std::cout << dynamic_array[i] << " ";
  }
  std::cout << "\n";

  // Сортування значень у динамічній пам'яті
  std::sort(dynamic_array, dynamic_array + size);

  std::cout << "  Відсортовані значення: ";
  for (int i = 0; i < size; ++i) {
    std::cout << dynamic_array[i] << " ";
  }
  std::cout << "\n";

  // Звільнення динамічної пам'яті
  delete[] dynamic_array;
}

void Project::PrintInfo() const {
  std::cout << "========================================\n"
            << "Проєкт #" << project_id_ << ": \"" << title << "\"\n"
            << "Замовник:                " << client_name << "\n"
            << "Термін (дедлайн):        " << deadline_days << " днів\n"
            << "Загальний бюджет:        " << std::fixed << std::setprecision(2)
            << total_budget_ << " грн\n"
            << "Витрачений бюджет:       " << spent_budget_ << " грн\n"
            << "Залишок бюджету:         " << GetRemainingBudget() << " грн\n"
            << "Необхідні ресурси:       " << required_resources_count_
            << " од.\n"
            << "Керівник (Worker):       " << lead_worker_.name << " ("
            << lead_worker_.position << ")\n"
            << "========================================\n";
}
