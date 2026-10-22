#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "project_hierarchy.h"
#include "project_management.h"

using namespace std;

static Worker g_static_worker(101, "Андрій Шевченко", "Lead Architect", 10,
                              55.0, 45, 15000.0, 95);
static Project g_static_project(1, "Корпоративний портал", "SoftServe", 60,
                                100000.0, 20000.0, 8, g_static_worker);

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));

  cout << "=========================================================\n";
  cout << "ЧАСТИНА 1. БАЗОВИЙ ФУНКЦІОНАЛ СИСТЕМИ (ЛАБОРАТОРНА РОБОТА 3)\n";
  cout << "=========================================================\n\n";

  cout << ">>> 1. Статичні елементи класу <<<\n";
  Worker::PrintTotalWorkersCount();
  Project::PrintTotalProjectsCount();
  cout << "Поточна кількість робітників через статичний метод: "
       << Worker::GetTotalWorkersCount() << "\n\n";

  cout << ">>> 2. Робота конструкторів базових класів <<<\n";
  Worker default_worker;
  Project default_project;
  default_worker.PrintInfo();
  default_project.PrintInfo();

  string engineering_dept = "Департамент розробки ПЗ";
  Worker param_worker(201, "Олексій Коваленко", "Senior Backend Dev", 6, 45.0,
                      34, 12000.0, 92, 9001, engineering_dept);
  param_worker.PrintInfo();

  ProjectModule composite_module("Платіжний шлюз API", 3, 18000.0);
  Project param_project(10, "Фінтех Екосистема", "PrivatBank", 120, 250000.0,
                        40000.0, 12, param_worker, 8001, composite_module);
  param_project.PrintInfo();

  Worker copy_worker(param_worker);
  Project copy_project(param_project);

  cout << "\n>>> 3. Способи створення об'єктів <<<\n";
  Worker worker_simple(301, "Максим Ткач", "QA Automation", 4, 32.0, 25, 6000.0,
                       86, 9002, engineering_dept);
  Worker worker_explicit = Worker(302, "Юлія Бойко", "UI/UX Designer", 5, 35.0,
                                  28, 7500.0, 89, 9003, engineering_dept);
  Worker worker_short = string("Роман Василенко");

  CalculateWorkerEfficiency(param_worker);
  CalculateWorkerEfficiency(&param_worker);

  cout << "\n>>> 4. Взаємодія за композицією та агрегацією <<<\n";
  Department security_dept("Департамент кібербезпеки", &param_worker);
  security_dept.ConductDepartmentSprint(4, 8000.0);

  param_project.DeliverCurrentModule(50);

  TaskAssignment assignment(
      &param_worker, &worker_simple, &param_project,
      "Розробка протоколу двофакторної автентифікації", 60, 22000.0);
  assignment.ExecuteAssignment();

  param_worker.SaveToFile("test_worker.txt");
  Worker loaded_worker;
  loaded_worker.LoadFromFile("test_worker.txt");

  param_project.SaveToFile("test_project.txt");
  Project loaded_project;
  loaded_project.LoadFromFile("test_project.txt");

  cout << "\n=========================================================\n";
  cout << "ЧАСТИНА 2. НОВИЙ ФУНКЦІОНАЛ: СПАДКУВАННЯ ТА ІЄРАРХІЯ КЛАСІВ\n";
  cout << "ТРЕТІЙ РІВЕНЬ СКЛАДНОСТІ (ПУНКТИ 1 - 9 ЗАВДАННЯ)\n";
  cout << "=========================================================\n\n";

  cout << ">>> ПУНКТ 1 ТА 5: Ієрархія класів (>= 8 полів на клас) та передача >= 5 аргументів конструктору базового класу <<<\n";
  SoftwareDeveloper dev1(
      701, "Дмитро Мельник", "Senior C++ Developer", 5, 42.0,
      "C++20 / STL / Boost", "CLion & Neovim", 8, 54, 88.5, true, 340, "feature/security-layer");
  dev1.PrintDeveloperDetails();

  cout << "\n>>> ПУНКТ 2: Керування доступом до 3 методів та 3 даних базового класу (public, protected, private) <<<\n";
  cout << "--- 2.1 Публічне наслідування (SoftwareDeveloper : public Worker) ---\n";
  dev1.DemonstrateAccessControl();

  cout << "\n--- 2.2 Захищене наслідування (ProjectSupervisor : protected Worker) ---\n";
  ProjectSupervisor supervisor1(
      801, "Валерій Сидоренко", "Project Supervisor", 9, 58.0,
      "Enterprise Banking Systems", 4, 75000.0, 7, 95.0, true, 12, "Київ, Офіс А");
  supervisor1.PrintSupervisorInfo();
  supervisor1.ConductSupervisorInspection();
  supervisor1.DemonstrateProtectedInheritance();

  cout << "\n>>> ПУНКТ 3: Додатковий похідний клас із закритим (private) наслідуванням та оперуванням методами різних класів <<<\n";
  SecurityAuditor auditor1(
      901, "Олександр Шевчук", "Lead Security Auditor", 8, 65.0,
      "AUD-CERT-9941", "ISO/IEC 27001 & SOC2", 14, 96.8, true, 28, 85000.0, "State Cyber Defense");
  auditor1.PrintAuditSummary();
  auditor1.DemonstratePrivateInheritanceAccess();

  cout << "\n--- Виклик методу, де об'єкт аудитора оперує методами різних класів ієрархії ---\n";
  auditor1.PerformFullSystemAudit(&param_project, &dev1, &supervisor1);

  cout << ">>> ПУНКТ 4: 3 додаткових класи для множинного наслідування та побудова відповідних об'єктів <<<\n";
  cout << "Клас 1: SoftwareArchitect (похідний від SoftwareDeveloper, >= 8 полів)\n";
  SoftwareArchitect architect1(
      702, "Ірина Мороз", "Principal Solution Architect", 11, 70.0,
      "C++ / Go / Python", "VS Code & Neovim", 15, 120, 93.0, true, 890, "architecture/core",
      "Event-Driven Microservices", "AWS Multi-Region Kubernetes", 18, 10, 150000.0, true, 24, "BLPRNT-FIN-2026");
  architect1.PrintArchitectDetails();
  architect1.DesignSystemArchitecture("Розподілений процесинг транзакцій");

  cout << "\nКлас 2: ProjectConsultant (доменний базовий клас, >= 8 полів)\n";
  ProjectConsultant consultant1(
      "Deloitte Strategy Advisory", "Cloud Infrastructure Cost & Risk", 12, 110.0, 32, 40.0, true, "STRAT-ROADMAP-Q4");
  consultant1.PrintConsultantInfo();
  consultant1.ProvideStrategicGuidance(&param_project);

  cout << "\nКлас 3: EngineeringDirector (Множинне наслідування від SoftwareArchitect та ProjectConsultant, >= 8 полів)\n";
  EngineeringDirector director1(
      703, "Ярослав Коваль", "VP of Engineering & Architecture", 14, 90.0,
      "C++ / Rust / Distributed Systems", "Neovim", 20, 210, 95.5, true, 1400, "main",
      "High-Load Reactive Architecture", "Hybrid Multi-Cloud AWS/GCP", 25, 10, 300000.0, true, 48, "BLPRNT-GLOBAL-01",
      "Gartner Executive Consulting", "Enterprise Digital Transformation", 10, 130.0, 45, 50.0, false, "STRAT-BOARD-2026",
      "Директорат стратегічних інженерних систем", 85, 2500000.0, 15, 96.5, true, 8, "Київ / Лондон");
  director1.PrintDirectorSummary();

  cout << "\n>>> ПУНКТ 6: Доступ до членів та методів базових класів через оператор :: та using <<<\n";
  cout << "1) Доступ через using в SecurityAuditor (public-доступ до Worker::name): " << auditor1.name << "\n";
  cout << "2) Доступ через using в SecurityAuditor (public-доступ до Worker::CalculateSalary): "
       << auditor1.CalculateSalary(160) << " $\n";
  cout << "3) Доступ через using в EngineeringDirector (PrintDeveloperDetails з SoftwareArchitect):\n";
  director1.PrintDeveloperDetails();
  cout << "4) Доступ через using в EngineeringDirector (PrintConsultantInfo з ProjectConsultant):\n";
  director1.PrintConsultantInfo();
  cout << "5) Прямий виклик методів базових класів з EngineeringDirector через ::\n";
  director1.SoftwareArchitect::OptimizeCloudInfrastructure();
  director1.ProjectConsultant::ProvideStrategicGuidance(&param_project);

  cout << "\n>>> ПУНКТ 7 ТА 8: Порядок виклику конструкторів та деструкторів, відслідковування входження у блоки <<<\n";
  cout << "--- 7.1 Демонстрація для простого наслідування (Worker -> SoftwareDeveloper) ---\n";
  cout << "Точка ПЕРЕД входженням у локальний блок простого наслідування.\n";
  {
    cout << "  [Вхід у локальний блок 1]\n";
    cout << "  Створення об'єкта SoftwareDeveloper dev_scope...\n";
    SoftwareDeveloper dev_scope(
        799, "Тимчасовий Тестувальник", "Junior Dev", 1, 20.0,
        "C++", "VS Code", 2, 5, 75.0, false, 15, "test/scope");
    cout << "  Об'єкт успішно створено. Виконання роботи всередині блоку:\n";
    dev_scope.WriteCode(250);
    dev_scope.RunUnitTests(10);
    cout << "  [Вихід з локального блоку 1: деструктори викликаються у зворотному порядку...]\n";
  }
  cout << "Точка ПІСЛЯ виходу з локального блоку простого наслідування.\n\n";

  cout << "--- 7.2 Демонстрація для множинного наслідування (SoftwareArchitect + ProjectConsultant -> EngineeringDirector) ---\n";
  cout << "Точка ПЕРЕД входженням у локальний блок множинного наслідування.\n";
  {
    cout << "  [Вхід у локальний блок 2]\n";
    cout << "  Створення об'єкта EngineeringDirector director_scope...\n";
    EngineeringDirector director_scope(
        788, "Олег Тимчасовий", "Interim Director", 10, 80.0,
        "C++", "CLion", 5, 20, 85.0, true, 200, "temp/exec",
        "SOA", "Azure", 6, 8, 80000.0, true, 10, "ARCH-TEMP",
        "Temp Advisory", "Audit", 8, 90.0, 10, 20.0, true, "ROAD-TEMP",
        "Тимчасовий департамент", 12, 400000.0, 3, 90.0, false, 2, "Львів");
    cout << "  Об'єкт успішно створено всередині блоку.\n";
    director_scope.AllocateStrategicBudget(50000.0);
    cout << "  [Вихід з локального блоку 2: деструктори викликаються у зворотному порядку...]\n";
  }
  cout << "Точка ПІСЛЯ виходу з локального блоку множинного наслідування.\n\n";

  cout << ">>> ПУНКТ 9: Комплексний сценарій функціонування системи та взаємодії усіх об'єктів <<<\n";
  cout << "Сценарій: Реалізація критичного релізу платіжної інфраструктури\n";
  cout << "1. Директор інженерії відкриває стратегічний реліз:\n";
  director1.ConductExecutiveReview(&param_project);
  director1.AllocateStrategicBudget(100000.0);

  cout << "2. Архітектор оптимізує хмарні мікросервіси та проєктує нові компоненти:\n";
  architect1.DesignSystemArchitecture("Модуль високошвидкісного криптографічного клірингу");
  architect1.OptimizeCloudInfrastructure();

  cout << "3. Розробник пише код та запускає unit-тести для проєкту:\n";
  dev1.WriteCode(650);
  dev1.RunUnitTests(25);
  dev1.CommitCode("feat: integrate cryptographic hardware acceleration");

  cout << "4. Керівник нагляду перевіряє прогрес та затверджує проміжну віху:\n";
  supervisor1.ConductSupervisorInspection();
  supervisor1.ApproveProjectMilestone("Етап 1: Криптографічний шлюз розгорнуто");

  cout << "5. Незалежний аудитор безпеки проводить комплексну верифікацію системи:\n";
  auditor1.PerformFullSystemAudit(&param_project, &dev1, &supervisor1);

  cout << "6. Завершення спринту проєкту:\n";
  param_project.DeliverCurrentModule(30);
  cout << "Підсумковий залишок бюджету проєкту \"" << param_project.title << "\": "
       << param_project.GetRemainingBudget() << " грн\n";

  cout << "\n=========================================================\n";
  cout << "ЗАВЕРШЕННЯ ПРОГРАМИ (ВИКЛИК ДЕСТРУКТОРІВ СТЕКОВИХ ОБ'ЄКТІВ)\n";
  cout << "=========================================================\n";

  return 0;
}
