#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "lab5_templates.h"
#include "personnel_system.h"
#include "project_management.h"

namespace {
void ClearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename Service> void AddEmployee(Service &service) {
  int id;
  double salary;
  int metric;
  std::string type;
  std::string name;
  std::string detail;
  std::cout << "Тип: 1-розробник, 2-тестувальник, 3-менеджер: ";
  std::getline(std::cin, type);
  std::cout << "ID: ";
  if (!(std::cin >> id))
    throw ValidationException("ID має бути числом");
  ClearInput();
  std::cout << "Ім'я: ";
  std::getline(std::cin, name);
  std::cout << "Зарплата: ";
  if (!(std::cin >> salary))
    throw ValidationException("Зарплата має бути числом");
  ClearInput();
  std::cout << "Спеціалізація: ";
  std::getline(std::cin, detail);
  std::cout << "Кількісний показник: ";
  if (!(std::cin >> metric))
    throw ValidationException("Показник має бути числом");
  ClearInput();
  service.Add(CreateEmployee(type, id, name, salary, detail, metric));
}

template <typename Service> void RemoveEmployee(Service &service) {
  int id;
  std::cout << "ID для видалення: ";
  if (!(std::cin >> id))
    throw ValidationException("ID має бути числом");
  ClearInput();
  service.RemoveById(id);
}

void DemonstrateLab5() {
  ProjectModule first("Авторизація", 4, 12000.0);
  ProjectModule second("Звіти", 2, 8000.0);
  std::cout << "Початкові модулі:\n";
  first.PrintInfo();
  second.PrintInfo();

  ProjectModule postfix_increment = first++;
  ++first;
  ProjectModule postfix_decrement = first--;
  --first;
  std::cout << "Постфіксний ++ повернув:\n";
  postfix_increment.PrintInfo();
  std::cout << "Постфіксний -- повернув:\n";
  postfix_decrement.PrintInfo();
  std::cout << "Стан після префіксних операцій:\n";
  first.PrintInfo();

  ProjectModule sum = first + second;
  ProjectModule difference = first - second;
  ProjectModule product = first * 1.5;
  ProjectModule quotient = first / 2.0;
  std::cout << "Оператори +, -, *, /:\n";
  sum.PrintInfo();
  difference.PrintInfo();
  product.PrintInfo();
  quotient.PrintInfo();

  first += second;
  first -= second;
  first *= 2.0;
  first /= 2.0;
  std::cout << "Стан після +=, -=, *=, /=:\n";
  first.PrintInfo();

  std::cout << "Шаблонна функція GreaterValue: "
            << ProjectModule::GreaterValue(24, 17) << '\n';
  ProjectRecord<int, std::string, ProjectModule, double, bool> record(
      501, "Шаблонний запис", first, 94.5, true);
  std::cout << "Шаблонний клас з п'ятьма типами: ID=" << record.GetId()
            << ", назва=" << record.GetName()
            << ", метрика=" << record.GetMetric()
            << ", активний=" << (record.GetState() ? "так" : "ні") << '\n';
  std::cout << "Користувацький тип ProjectModule у шаблоні:\n";
  record.GetObject().PrintInfo();
}
}

int main() {
  ServiceStatic static_service;
  ServiceDynamic dynamic_service;
  int choice = -1;
  while (choice != 0) {
    std::cout
        << "\n1 Додати до статичного  2 Додати до динамічного  3 Видалити зі "
           "статичного\n"
        << "4 Видалити з динамічного  5 Показати сховища  6 Зберегти обидва\n"
        << "7 Завантажити обидва  8 Поліморфізм  9 Винятки  10 Лабораторна 5  "
           "0 Вихід\nВибір: ";
    if (!(std::cin >> choice)) {
      ClearInput();
      std::cout << "Некоректний вибір.\n";
      continue;
    }
    ClearInput();
    try {
      if (choice == 1)
        AddEmployee(static_service);
      else if (choice == 2)
        AddEmployee(dynamic_service);
      else if (choice == 3)
        RemoveEmployee(static_service);
      else if (choice == 4)
        RemoveEmployee(dynamic_service);
      else if (choice == 5) {
        static_service.PrintAll(std::cout);
        dynamic_service.PrintAll(std::cout);
      } else if (choice == 6) {
        static_service.SaveAll("static_personnel.txt");
        dynamic_service.SaveAll("dynamic_personnel.txt");
        std::cout << "Дані збережено.\n";
      } else if (choice == 7) {
        static_service.LoadAll("static_personnel.txt");
        dynamic_service.LoadAll("dynamic_personnel.txt");
        std::cout << "Дані завантажено.\n";
      } else if (choice == 8) {
        if (dynamic_service.Size() > 0)
          DemonstratePolymorphism(dynamic_service.At(0));
        else if (static_service.Size() > 0)
          DemonstratePolymorphism(static_service.At(0));
        else
          std::cout << "Спочатку додайте працівника.\n";
      } else if (choice == 9)
        DemonstrateExceptions();
      else if (choice == 10)
        DemonstrateLab5();
      else if (choice != 0)
        std::cout << "Немає такого пункту.\n";
    } catch (const PersonnelException &error) {
      std::cout << "Помилка: " << error.what() << '\n';
    }
  }
  return 0;
}
