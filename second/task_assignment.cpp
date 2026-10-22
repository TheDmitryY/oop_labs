#include <iostream>
#include <string>

#include "project_management.h"

using namespace std;

TaskAssignment::TaskAssignment()
    : developer_(nullptr),
      reviewer_(nullptr),
      project_(nullptr),
      task_title_("Невизначене завдання"),
      planned_hours_(0),
      task_cost_(0.0),
      is_completed_(false) {
  cout << "[TaskAssignment] Створено порожнє призначення завдання\n";
}

TaskAssignment::TaskAssignment(Worker* dev, Worker* rev, Project* proj,
                               const string& title, int hours, double cost)
    : developer_(dev),
      reviewer_(rev),
      project_(proj),
      task_title_(title),
      planned_hours_(hours),
      task_cost_(cost),
      is_completed_(false) {
  cout << "[TaskAssignment] Створено призначення завдання через асоціацію: "
       << task_title_ << "\n";
}

TaskAssignment::TaskAssignment(const TaskAssignment& other)
    : developer_(other.developer_),
      reviewer_(other.reviewer_),
      project_(other.project_),
      task_title_(other.task_title_),
      planned_hours_(other.planned_hours_),
      task_cost_(other.task_cost_),
      is_completed_(other.is_completed_) {
  cout << "[TaskAssignment] Скопійовано призначення завдання: " << task_title_
       << "\n";
}

TaskAssignment& TaskAssignment::operator=(const TaskAssignment& other) {
  if (this != &other) {
    developer_ = other.developer_;
    reviewer_ = other.reviewer_;
    project_ = other.project_;
    task_title_ = other.task_title_;
    planned_hours_ = other.planned_hours_;
    task_cost_ = other.task_cost_;
    is_completed_ = other.is_completed_;
  }
  return *this;
}

TaskAssignment::~TaskAssignment() {
  cout << "[TaskAssignment] Знищено призначення завдання: " << task_title_
       << "\n";
}

bool TaskAssignment::ExecuteAssignment() {
  cout << "\n>>> Виконання завдання через клас асоціацій: '" << task_title_
       << "' <<<\n";
  if (!developer_ || !reviewer_ || !project_) {
    cout << "Помилка: Не всі учасники асоціації (розробник, рев'юер, проєкт) "
            "присутні!\n";
    return false;
  }

  if (project_->GetRemainingBudget() < task_cost_) {
    cout << "Помилка: У проєкті '" << project_->title
         << "' недостатньо бюджету для виконання завдання!\n";
    return false;
  }

  cout << "1) Проєкт '" << project_->title << "' виділяє кошти (" << task_cost_
       << " грн)\n";
  project_->AddResources(1, task_cost_);

  cout << "2) Розробник " << developer_->name
       << " реалізує функціонал за планом: " << planned_hours_ << " год\n";
  developer_->AllocateBudget(task_cost_ * 0.7);
  developer_->CompleteTasks(2, task_cost_ * 0.7);

  cout << "3) Рев'юер / QA " << reviewer_->name
       << " проводить перевірку коду та тестування\n";
  reviewer_->AllocateBudget(task_cost_ * 0.3);
  reviewer_->CompleteTasks(1, task_cost_ * 0.3);

  is_completed_ = true;
  cout << "Завдання '" << task_title_
       << "' успішно виконано через взаємодію 3-х об'єктів!\n";
  return true;
}

void TaskAssignment::PrintInfo() const {
  cout << "========================================\n"
       << "Клас асоціацій: TaskAssignment\n"
       << "Завдання:                " << task_title_ << "\n"
       << "Заплановано годин:       " << planned_hours_ << " год\n"
       << "Бюджет завдання:         " << task_cost_ << " грн\n"
       << "Стан виконання:          "
       << (is_completed_ ? "Виконано" : "В роботі") << "\n"
       << "Проєкт (Project*):       "
       << (project_ ? project_->title : "відсутній") << "\n"
       << "Розробник (Worker*):     "
       << (developer_ ? developer_->name : "відсутній") << "\n"
       << "Рев'юер / QA (Worker*):  "
       << (reviewer_ ? reviewer_->name : "відсутній") << "\n"
       << "========================================\n";
}
