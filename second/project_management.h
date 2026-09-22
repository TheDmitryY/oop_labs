// Copyright 2026 Dmitriy Mankevych
// Пункт 14: Дотримання правил Google C++ Style Guide
// Пункт 15: Файл 1 з 3 - Заголовний h-файл із визначенням класів

#ifndef PROJECT_MANAGEMENT_H_
#define PROJECT_MANAGEMENT_H_

#include <fstream>
#include <iostream>
#include <string>

// ============================================================================
// Пункт 1: Клас 1 - Worker (Робітник) за варіантом 9 ("Менеджмент проєкту")
// Клас містить 8 полів даних (3 загальних та 5 приватних).
// ============================================================================
class Worker {
 public:
  // Пункт 2: 3 загальні (public) елементи (поля даних)
  std::string name;      // ПІБ робітника
  std::string position;  // Посада (Developer, QA, PM тощо)
  int experience_years;  // Досвід роботи (років)

  // Конструктори
  Worker();
  Worker(int id, const std::string& worker_name,
         const std::string& worker_position, int exp_years, double rate,
         int tasks, double budget, int productivity);

  // Пункт 4: 6 методів опрацювання описаних даних:
  // 1. Обчислення заробітної плати на основі ставки, продуктивності та досвіду
  double CalculateSalary(int hours_worked) const;

  // 2. Метод виконання завдань (перевантажений варіант 1)
  void CompleteTasks();

  // 3. Метод виконання завдань (перевантажений варіант 2: з кількістю та
  // бюджетом)
  void CompleteTasks(int tasks_count, double budget_spent);

  // 4. Метод виділення додаткового бюджету робітнику
  void AllocateBudget(double amount);

  // 5. Метод, що приймає як параметр об'єкт класу Worker (порівняння досвіду)
  bool CompareExperience(const Worker& other) const;

  // 6. Метод, що повертає тип класу Worker (підвищення на посаді та нові умови)
  Worker CreatePromotedWorker(const std::string& new_position,
                              double bonus_rate) const;

  // Пункт 5: Методи для запису у файл та читання з файлу
  bool SaveToFile(const std::string& filename) const;
  bool LoadFromFile(const std::string& filename);
  void WriteToStream(std::ostream& out) const;
  bool ReadFromStream(std::istream& in);

  // Пункт 12: Додатковий метод, що виділяє випадкову величину динамічної
  // пам'яті, розміщує множину значень цілочисельного поля та сортує їх
  void AllocateAndSortMemory() const;

  // Геттери та сеттери для приватних полів
  int GetWorkerId() const { return worker_id_; }
  double GetHourlyRate() const { return hourly_rate_; }
  int GetCompletedTasks() const { return completed_tasks_; }
  double GetAllocatedBudget() const { return allocated_budget_; }
  int GetProductivityScore() const { return productivity_score_; }

  void SetHourlyRate(double rate) { hourly_rate_ = rate; }
  void SetProductivityScore(int score) { productivity_score_ = score; }

  // Метод для виведення інформації про робітника
  void PrintInfo() const;

 private:
  // Пункт 2: 5 приватних (private) елементів (полів даних)
  int worker_id_;            // Унікальний ідентифікатор робітника
  double hourly_rate_;       // Погодинна ставка оплати
  int completed_tasks_;      // Кількість виконаних завдань
  double allocated_budget_;  // Бюджет, виділений робітнику на виконання завдань
  int productivity_score_;   // Оцінка продуктивності (1-100)
};

// ============================================================================
// Пункт 1: Клас 2 - Project (Проєкт) за варіантом 9 ("Менеджмент проєкту")
// Клас містить 8 полів даних (3 загальних та 5 приватних).
// ============================================================================
class Project {
 public:
  // Пункт 2: 3 загальні (public) елементи (поля даних)
  std::string title;        // Назва проєкту
  std::string client_name;  // Замовник проєкту
  int deadline_days;        // Термін виконання у днях

  // Конструктори
  Project();
  Project(int id, const std::string& proj_title, const std::string& client,
          int days, double total_budget, double spent_budget, int resources,
          const Worker& lead);

  // Пункт 4: 6 методів опрацювання описаних даних:
  // 1. Отримання залишку доступного бюджету
  double GetRemainingBudget() const;

  // 2. Додавання ресурсів до проєкту (перевантажений варіант 1)
  void AddResources(int count);

  // 3. Додавання ресурсів з урахуванням вартості (перевантажений варіант 2)
  void AddResources(int count, double additional_cost);

  // 4. Виділення бюджету з проєкту відповідальному робітнику (керівнику)
  bool AssignBudgetToLead(double amount);

  // 5. Метод, що приймає як параметр об'єкт класу Project (об'єднання проєктів)
  void MergeProject(const Project& other);

  // 6. Метод, що повертає тип класу Project (створення підпроєкту)
  Project CreateSubproject(const std::string& sub_title,
                           double sub_budget) const;

  // Пункт 10: Метод для демонстрації сценарію взаємодії робітника і проєкту
  // Виконання спринту: робітник витрачає бюджет, ресурси і завершує завдання
  bool ExecuteSprint(int tasks_to_complete, double sprint_cost);

  // Пункт 5: Методи для запису у файл та читання з файлу
  bool SaveToFile(const std::string& filename) const;
  bool LoadFromFile(const std::string& filename);
  void WriteToStream(std::ostream& out) const;
  bool ReadFromStream(std::istream& in);

  // Пункт 12: Додатковий метод, що виділяє випадкову величину динамічної
  // пам'яті, розміщує множину значень цілочисельного поля та сортує їх
  void AllocateAndSortMemory() const;

  // Геттери та сеттери для приватних полів
  int GetProjectId() const { return project_id_; }
  double GetTotalBudget() const { return total_budget_; }
  double GetSpentBudget() const { return spent_budget_; }
  int GetRequiredResourcesCount() const { return required_resources_count_; }
  const Worker& GetLeadWorker() const { return lead_worker_; }
  Worker& GetLeadWorker() { return lead_worker_; }

  void SetLeadWorker(const Worker& lead) { lead_worker_ = lead; }

  // Метод для виведення інформації про проєкт
  void PrintInfo() const;

 private:
  // Пункт 2: 5 приватних (private) елементів (полів даних)
  int project_id_;                // ID проєкту
  double total_budget_;           // Загальний бюджет проєкту
  double spent_budget_;           // Витрачений бюджет
  int required_resources_count_;  // Кількість необхідних ресурсів (сервери,
                                  // ліцензії тощо)

  // Пункт 3: Зв'язок двох об'єктів шляхом розміщення об'єкта класу Worker
  // у класі Project як поля даних без використання дружніх функцій
  Worker lead_worker_;  // Відповідальний робітник / керівник проєкту
};

#endif  // PROJECT_MANAGEMENT_H_
