
#ifndef PROJECT_MANAGEMENT_H_
#define PROJECT_MANAGEMENT_H_

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Worker {
 public:
  string name;
  string position;
  int experience_years;

  Worker();
  Worker(int id, const string& worker_name,
         const string& worker_position, int exp_years, double rate,
         int tasks, double budget, int productivity);

  double CalculateSalary(int hours_worked) const;

  void CompleteTasks();

  void CompleteTasks(int tasks_count, double budget_spent);

  void AllocateBudget(double amount);

  bool CompareExperience(const Worker& other) const;

  Worker CreatePromotedWorker(const string& new_position,
                              double bonus_rate) const;

  bool SaveToFile(const string& filename) const;
  bool LoadFromFile(const string& filename);
  void WriteToStream(ostream& out) const;
  bool ReadFromStream(istream& in);

  void AllocateAndSortMemory() const;

  int GetWorkerId() const { return worker_id_; }
  double GetHourlyRate() const { return hourly_rate_; }
  int GetCompletedTasks() const { return completed_tasks_; }
  double GetAllocatedBudget() const { return allocated_budget_; }
  int GetProductivityScore() const { return productivity_score_; }

  void SetHourlyRate(double rate) { hourly_rate_ = rate; }
  void SetProductivityScore(int score) { productivity_score_ = score; }

  void PrintInfo() const;

 private:
  int worker_id_;
  double hourly_rate_;
  int completed_tasks_;
  double allocated_budget_;
  int productivity_score_;   
};

class Project {
 public:
  string title;
  string client_name;
  int deadline_days;

  Project();
  Project(int id, const string& proj_title, const string& client,
          int days, double total_budget, double spent_budget, int resources,
          const Worker& lead);

  double GetRemainingBudget() const;

  void AddResources(int count);

  void AddResources(int count, double additional_cost);

  bool AssignBudgetToLead(double amount);

  void MergeProject(const Project& other);

  Project CreateSubproject(const string& sub_title,
                           double sub_budget) const;

  bool ExecuteSprint(int tasks_to_complete, double sprint_cost);

  bool SaveToFile(const string& filename) const;
  bool LoadFromFile(const string& filename);
  void WriteToStream(ostream& out) const;
  bool ReadFromStream(istream& in);

  void AllocateAndSortMemory() const;

  int GetProjectId() const { return project_id_; }
  double GetTotalBudget() const { return total_budget_; }
  double GetSpentBudget() const { return spent_budget_; }
  int GetRequiredResourcesCount() const { return required_resources_count_; }
  const Worker& GetLeadWorker() const { return lead_worker_; }
  Worker& GetLeadWorker() { return lead_worker_; }

  void SetLeadWorker(const Worker& lead) { lead_worker_ = lead; }

  void PrintInfo() const;

 private:
  int project_id_;
  double total_budget_;
  double spent_budget_;
  int required_resources_count_;
  Worker lead_worker_;
};

#endif
