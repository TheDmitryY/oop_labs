#include <algorithm>
#include <iostream>

#include "project_management.h"

using namespace std;

ProjectModule::ProjectModule()
    : module_name_("Базовий модуль"),
      complexity_(1),
      allocated_funds_(5000.0),
      progress_percent_(0) {
  cout << "[ProjectModule] Створено модуль за замовчуванням: " << module_name_
       << "\n";
}

ProjectModule::ProjectModule(const string& module_name, int complexity,
                             double allocated_funds)
    : module_name_(module_name),
      complexity_(complexity),
      allocated_funds_(allocated_funds),
      progress_percent_(0) {
  cout << "[ProjectModule] Створено модуль: " << module_name_ << "\n";
}

ProjectModule::ProjectModule(const ProjectModule& other)
    : module_name_(other.module_name_),
      complexity_(other.complexity_),
      allocated_funds_(other.allocated_funds_),
      progress_percent_(other.progress_percent_) {
  cout << "[ProjectModule] Скопійовано модуль: " << module_name_ << "\n";
}

ProjectModule& ProjectModule::operator=(const ProjectModule& other) {
  if (this != &other) {
    module_name_ = other.module_name_;
    complexity_ = other.complexity_;
    allocated_funds_ = other.allocated_funds_;
    progress_percent_ = other.progress_percent_;
  }
  return *this;
}

ProjectModule::~ProjectModule() {
  cout << "[ProjectModule] Знищено модуль: " << module_name_ << "\n";
}

void ProjectModule::Execute(int progress) {
  progress_percent_ = min(100, progress_percent_ + progress);
  cout << "[ProjectModule " << module_name_
       << "] Виконання модуля. Поточний прогрес: " << progress_percent_
       << "%\n";
}

void ProjectModule::PrintInfo() const {
  cout << "  [Модуль] Назва: " << module_name_
       << ", Складність: " << complexity_ << ", Бюджет: " << allocated_funds_
       << " грн"
       << ", Прогрес: " << progress_percent_ << "%\n";
}
