#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "personnel_system.h"

namespace {
void ClearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename Service>
void AddEmployee(Service& service) {
  int id;
  double salary;
  int metric;
  std::string type;
  std::string name;
  std::string detail;
  std::cout << "Тип: 1-розробник, 2-тестувальник, 3-менеджер: ";
  std::getline(std::cin, type);
  std::cout << "ID: ";
  if (!(std::cin >> id)) throw ValidationException("ID має бути числом");
  ClearInput();
  std::cout << "Ім'я: ";
  std::getline(std::cin, name);
  std::cout << "Зарплата: ";
  if (!(std::cin >> salary)) throw ValidationException("Зарплата має бути числом");
  ClearInput();
  std::cout << "Спеціалізація: ";
  std::getline(std::cin, detail);
  std::cout << "Кількісний показник: ";
  if (!(std::cin >> metric)) throw ValidationException("Показник має бути числом");
  ClearInput();
  service.Add(CreateEmployee(type, id, name, salary, detail, metric));
}

template <typename Service>
void RemoveEmployee(Service& service) {
  int id;
  std::cout << "ID для видалення: ";
  if (!(std::cin >> id)) throw ValidationException("ID має бути числом");
  ClearInput();
  service.RemoveById(id);
}
}

int main() {
  ServiceStatic static_service;
  ServiceDynamic dynamic_service;
  int choice = -1;
  while (choice != 0) {
    std::cout << "\n1 Додати до статичного  2 Додати до динамічного  3 Видалити зі статичного\n"
              << "4 Видалити з динамічного  5 Показати сховища  6 Зберегти обидва\n"
              << "7 Завантажити обидва  8 Поліморфізм  9 Винятки  0 Вихід\nВибір: ";
    if (!(std::cin >> choice)) { ClearInput(); std::cout << "Некоректний вибір.\n"; continue; }
    ClearInput();
    try {
      if (choice == 1) AddEmployee(static_service);
      else if (choice == 2) AddEmployee(dynamic_service);
      else if (choice == 3) RemoveEmployee(static_service);
      else if (choice == 4) RemoveEmployee(dynamic_service);
      else if (choice == 5) { static_service.PrintAll(std::cout); dynamic_service.PrintAll(std::cout); }
      else if (choice == 6) { static_service.SaveAll("static_personnel.txt"); dynamic_service.SaveAll("dynamic_personnel.txt"); std::cout << "Дані збережено.\n"; }
      else if (choice == 7) { static_service.LoadAll("static_personnel.txt"); dynamic_service.LoadAll("dynamic_personnel.txt"); std::cout << "Дані завантажено.\n"; }
      else if (choice == 8) { if (dynamic_service.Size() > 0) DemonstratePolymorphism(dynamic_service.At(0)); else if (static_service.Size() > 0) DemonstratePolymorphism(static_service.At(0)); else std::cout << "Спочатку додайте працівника.\n"; }
      else if (choice == 9) DemonstrateExceptions();
      else if (choice != 0) std::cout << "Немає такого пункту.\n";
    } catch (const PersonnelException& error) { std::cout << "Помилка: " << error.what() << '\n'; }
  }
  return 0;
}
