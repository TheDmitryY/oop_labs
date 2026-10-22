#include <iostream>
#include <string>

#include "project_management.h"

using namespace std;

Department::Department()
    : department_name_("Загальний відділ"), manager_(nullptr) {
  cout << "[Department] Створено підрозділ (за замовчуванням): "
       << department_name_ << "\n";
}

Department::Department(const string& name, Worker* manager)
    : department_name_(name), manager_(manager) {
  cout << "[Department] Створено підрозділ: " << department_name_
       << " з агрегованим менеджером: "
       << (manager_ ? manager_->name : "відсутній") << "\n";
}

Department::Department(const Department& other)
    : department_name_(other.department_name_), manager_(other.manager_) {
  cout << "[Department] Скопійовано підрозділ: " << department_name_ << "\n";
}

Department& Department::operator=(const Department& other) {
  if (this != &other) {
    department_name_ = other.department_name_;
    manager_ = other.manager_;
  }
  return *this;
}

Department::~Department() {
  cout << "[Department] Знищено підрозділ: " << department_name_
       << " (агрегований робітник залишається живим)\n";
}

void Department::AssignManager(Worker* manager) {
  manager_ = manager;
  cout << "[Department " << department_name_
       << "] Призначено нового менеджера: "
       << (manager_ ? manager_->name : "немає") << "\n";
}

void Department::ConductDepartmentSprint(int tasks, double budget_allocation) {
  cout << "\n[Department " << department_name_
       << "] Проведення внутрішнього спринту підрозділу...\n";
  if (manager_) {
    manager_->AllocateBudget(budget_allocation);
    manager_->CompleteTasks(tasks, budget_allocation * 0.6);
    cout << "Менеджер підрозділу успішно скоординував та виконав завдання.\n";
  } else {
    cout << "Помилка: У підрозділі відсутній менеджер для координації!\n";
  }
}

void Department::PrintInfo() const {
  cout << "========================================\n"
       << "Підрозділ (агрегація):   " << department_name_ << "\n";
  if (manager_) {
    cout << "Менеджер (Worker*):      " << manager_->name << " ("
         << manager_->position << "), ID: " << manager_->GetWorkerId() << "\n";
  } else {
    cout << "Менеджер (Worker*):      не призначений\n";
  }
  cout << "========================================\n";
}
