#include <cstdlib>
#include <ctime>
#include <iostream>

#include "project_management.h"

using namespace std;

static Worker static_worker1(101, "Андрій Шевченко", "Lead Architect", 10, 55.0,
                             45, 15000.0, 95);
static Worker static_worker2(102, "Марія Бондаренко", "Senior QA Engineer", 6,
                             35.0, 30, 8000.0, 90);
static Project static_project1(1, "Корпоративний портал", "SoftServe", 60,
                               100000.0, 20000.0, 8, static_worker1);
static Project static_project2(2, "Мобільний банкінг", "Monobank", 90, 150000.0,
                               40000.0, 12, static_worker2);
static Project static_project3(3, "Хмарна безпека", "CyberDefense", 45, 75000.0,
                               15000.0, 6, static_worker1);

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));

  cout << ">>> [Пункт 6] Створення 5 об'єктів у динамічній пам'яті <<<\n";
  Worker* dyn_worker1 = new Worker(201, "Олег Мельник", "DevOps Engineer", 5,
                                   42.0, 28, 7000.0, 88);
  Worker* dyn_worker2 = new Worker(202, "Ірина Ковальчук", "Frontend Developer",
                                   3, 30.0, 19, 4500.0, 84);
  Project* dyn_project1 =
      new Project(10, "CRM Система логістики", "GlobalLogistics", 120, 180000.0,
                  35000.0, 15, *dyn_worker1);
  Project* dyn_project2 =
      new Project(11, "Платіжний мікросервіс", "FinTech Solutions", 75,
                  120000.0, 25000.0, 10, *dyn_worker2);
  Project* dyn_project3 =
      new Project(12, "ШІ-Модуль прогнозування", "DataFuture", 150, 250000.0,
                  60000.0, 20, *dyn_worker1);
  cout << "5 об'єктів успішно виділено через оператор new.\n\n";

 
  cout << ">>> [Пункт 7] Визначення 2 масивів об'єктів <<<\n";
  const int kWorkerCount = 3;
  Worker workers_array[kWorkerCount] = {
      Worker(301, "Василь Сидоренко", "Backend Developer", 4, 32.0, 22, 5000.0,
             85),
      Worker(302, "Олена Ткаченко", "UI/UX Designer", 3, 28.0, 16, 4000.0, 82),
      Worker(303, "Дмитро Гриценко", "Project Manager", 8, 48.0, 42, 10000.0,
             93)};

  const int kProjectCount = 3;
  Project projects_array[kProjectCount] = {
      Project(21, "E-Commerce Платформа", "Rozetka", 100, 160000.0, 45000.0, 14,
              workers_array[2]),
      Project(22, "Логістичний трекер", "Nova Poshta", 80, 110000.0, 30000.0, 9,
              workers_array[0]),
      Project(23, "Дизайн-система бренду", "Prom UA", 40, 40000.0, 12000.0, 5,
              workers_array[1])};
  cout << "Масив 1: " << kWorkerCount << " робітників.\n";
  cout << "Масив 2: " << kProjectCount << " проєктів.\n\n";
  cout << ">>> [Пункт 8] Демонстрація роботи з об'єктами масивів <<<\n";
  cout << "\n--- Робота з масивом робітників (workers_array) ---\n";
  for (int i = 0; i < kWorkerCount; ++i) {
    workers_array[i].PrintInfo();
    double salary = workers_array[i].CalculateSalary(160);
    cout << "  Розрахована зарплата за 160 год: " << salary << " $\n";
    workers_array[i].CompleteTasks();
    cout << "\n";
  }

  cout << "--- Робота з масивом проєктів (projects_array) ---\n";
  for (int i = 0; i < kProjectCount; ++i) {
    projects_array[i].PrintInfo();
    projects_array[i].AddResources(2);
    projects_array[i].AssignBudgetToLead(3000.0);
    cout << "  Залишок бюджету: " << projects_array[i].GetRemainingBudget()
              << " грн\n\n";
  }
  cout
      << ">>> [Пункт 9] Демонстрація роботи УСІХ методів обох класів <<<\n";

  cout << "\n--- [Клас Worker: Демонстрація методів] ---\n";
  Worker test_worker(401, "Сергій Кравченко", "Middle C++ Dev", 3, 25.0, 10,
                     2000.0, 80);
  test_worker.PrintInfo();

  cout << "\n1) Worker::CalculateSalary(160):\n";
  cout << "Зарплата Сергія за 160 годин: "
            << test_worker.CalculateSalary(160) << " $\n";

  cout << "\n2) Worker::CompleteTasks() [перевантажений 1]:\n";
  test_worker.CompleteTasks();

  cout << "\n3) Worker::CompleteTasks(4, 500.0) [перевантажений 2]:\n";
  test_worker.CompleteTasks(4, 500.0);

  cout << "\n4) Worker::AllocateBudget(1500.0):\n";
  test_worker.AllocateBudget(1500.0);

  cout << "\n5) Worker::CompareExperience (приймає об'єкт класу):\n";
  bool more_exp = test_worker.CompareExperience(static_worker1);
  cout << "Чи має Сергій більший або рівний досвід за Андрія? "
            << (more_exp ? "Так" : "Ні") << "\n";

  cout << "\n6) Worker::CreatePromotedWorker (повертає об'єкт класу):\n";
  Worker promoted_worker =
      test_worker.CreatePromotedWorker("Senior C++ Dev", 15.0);
  promoted_worker.PrintInfo();

  cout << "\n7) Worker::SaveToFile та Worker::LoadFromFile:\n";
  test_worker.SaveToFile("test_worker.txt");
  cout << "Дані Сергія записано у файл 'test_worker.txt'.\n";

  Worker loaded_worker;
  loaded_worker.LoadFromFile("test_worker.txt");
  cout << "Зчитано дані робітника з файлу 'test_worker.txt':\n";
  loaded_worker.PrintInfo();

  cout << "\n8) Worker::AllocateAndSortMemory [Пункт 12]:\n";
  test_worker.AllocateAndSortMemory();

  cout << "\n--- [Клас Project: Демонстрація методів] ---\n";
  Project test_project(50, "Інтернет-магазин запчастин", "AutoParts Ltd", 60,
                       80000.0, 10000.0, 4, test_worker);
  test_project.PrintInfo();

  cout << "\n1) Project::GetRemainingBudget():\n";
  cout << "Залишок бюджету проєкту: " << test_project.GetRemainingBudget()
            << " грн\n";

  cout << "\n2) Project::AddResources(3) [перевантажений 1]:\n";
  test_project.AddResources(3);

  cout << "\n3) Project::AddResources(2, 4500.0) [перевантажений 2]:\n";
  test_project.AddResources(2, 4500.0);

  cout << "\n4) Project::AssignBudgetToLead(6000.0):\n";
  test_project.AssignBudgetToLead(6000.0);

  cout << "\n5) Project::MergeProject (приймає об'єкт класу):\n";
  Project secondary_project(51, "Модуль складського обліку", "AutoParts Ltd",
                            30, 25000.0, 5000.0, 2, static_worker2);
  test_project.MergeProject(secondary_project);

  cout << "\n6) Project::CreateSubproject (повертає об'єкт класу):\n";
  Project sub_proj =
      test_project.CreateSubproject("Підсистема онлайн-оплати", 15000.0);
  sub_proj.PrintInfo();

  cout << "\n7) Project::SaveToFile та Project::LoadFromFile:\n";
  test_project.SaveToFile("test_project.txt");
  cout << "Дані проєкту записано у файл 'test_project.txt'.\n";

  Project loaded_project;
  loaded_project.LoadFromFile("test_project.txt");
  cout << "Зчитано дані проєкту з файлу 'test_project.txt':\n";
  loaded_project.PrintInfo();

  cout << "\n8) Project::AllocateAndSortMemory [Пункт 12]:\n";
  test_project.AllocateAndSortMemory();

  cout << "\n>>> [Пункт 10] Сценарій взаємодії двох об'єктів (Project & "
               "Worker) <<<\n";
  cout << "Сценарій: Замовник 'Fintech Ukraine' замовляє розробку "
               "платіжного шлюзу.\n";
  cout
      << "Менеджер призначає провідного розробника та розпочинає роботу.\n";

  Worker lead_dev(601, "Ярослав Мудрий", "Lead Software Architect", 9, 60.0, 50,
                  0.0, 95);
  Project client_project(100, "Національний платіжний шлюз", "Fintech Ukraine",
                         90, 200000.0, 0.0, 10, lead_dev);

  cout << "\nПочатковий стан проєкту та відповідального робітника:\n";
  client_project.PrintInfo();

  cout << "\n--- Етап 1: Виконання першого спринту розробки ---\n";
  client_project.ExecuteSprint(6, 35000.0);

  cout << "\n--- Етап 2: Додаткові ресурси (сервери та сертифікати) ---\n";
  client_project.AddResources(3, 12000.0);

  cout
      << "\n--- Етап 3: Виконання другого спринту тестування та деплою ---\n";
  client_project.ExecuteSprint(8, 40000.0);

  cout << "\nКінцевий стан проєкту після взаємодії:\n";
  client_project.PrintInfo();

  cout
      << "\n>>> [Пункт 11] Використання покажчиків на екземпляри класів <<<\n";
  Worker* worker_pointer = &static_worker1;
  cout << "Покажчик worker_pointer вказує на об'єкт static_worker1:\n";
  cout << "  Ім'я робітника (через покажчик ->): " << worker_pointer->name
            << "\n";
  cout << "  Посада: " << worker_pointer->position << "\n";
  worker_pointer->CompleteTasks(2, 400.0);

  Project* project_pointer = dyn_project1;
  cout << "\nПокажчик project_pointer вказує на dyn_project1:\n";
  cout << "  Назва проєкту (через покажчик ->): " << project_pointer->title
            << "\n";
  cout << "  Залишок бюджету: " << project_pointer->GetRemainingBudget()
            << " грн\n";
  project_pointer->AddResources(2, 2500.0);

  cout << "\n>>> [Пункт 12] Додатковий метод: випадкова пам'ять та "
               "сортування <<<\n";
  cout << "Тест 1: Для Worker (поле productivity_score_):\n";
  dyn_worker1->AllocateAndSortMemory();

  cout << "\nТест 2: Для Project (поле deadline_days):\n";
  dyn_project2->AllocateAndSortMemory();

  delete dyn_worker1;
  delete dyn_worker2;
  delete dyn_project1;
  delete dyn_project2;
  delete dyn_project3;
  cout << "\n[Завершення] Всі 5 динамічних об'єктів успішно звільнено "
               "(delete).\n";

  return 0;
}
