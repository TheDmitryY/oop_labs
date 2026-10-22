#ifndef PROJECT_MANAGEMENT_H_
#define PROJECT_MANAGEMENT_H_

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class ProjectModule {
public:
  ProjectModule();
  ProjectModule(const std::string &module_name, int complexity,
                double allocated_funds);
  ProjectModule(const ProjectModule &other);
  ProjectModule &operator=(const ProjectModule &other);
  ~ProjectModule();

  ProjectModule &operator++();
  ProjectModule operator++(int);
  ProjectModule &operator--();
  ProjectModule operator--(int);
  ProjectModule operator+(const ProjectModule &other) const;
  ProjectModule operator-(const ProjectModule &other) const;
  ProjectModule operator*(double multiplier) const;
  ProjectModule operator/(double divisor) const;
  ProjectModule &operator+=(const ProjectModule &other);
  ProjectModule &operator-=(const ProjectModule &other);
  ProjectModule &operator*=(double multiplier);
  ProjectModule &operator/=(double divisor);

  template <typename T> static T GreaterValue(const T &first, const T &second) {
    return first > second ? first : second;
  }

  void Execute(int progress);
  void PrintInfo() const;

  const std::string &GetModuleName() const { return module_name_; }
  int GetComplexity() const { return complexity_; }
  double GetAllocatedFunds() const { return allocated_funds_; }
  int GetProgress() const { return progress_percent_; }

private:
  std::string module_name_;
  int complexity_;
  double allocated_funds_;
  int progress_percent_;
};

class Worker {
public:
  static const std::string kDefaultDepartment;

  std::string name;
  std::string position;
  int experience_years;

  Worker();
  Worker(int id, const std::string &worker_name,
         const std::string &worker_position, int exp_years, double rate,
         int tasks, double budget, int productivity, int code,
         const std::string &dept);
  Worker(int id, const std::string &worker_name,
         const std::string &worker_position, int exp_years, double rate,
         int tasks, double budget, int productivity);
  Worker(int id, const std::string &worker_name,
         const std::string &worker_position, int exp_years, double rate);
  Worker(const std::string &worker_name);
  Worker(const Worker &other);
  Worker &operator=(const Worker &other);
  virtual ~Worker();

  double CalculateSalary(int hours_worked) const;
  void CompleteTasks();
  void CompleteTasks(int tasks_count, double budget_spent);
  void AllocateBudget(double amount);
  bool CompareExperience(const Worker &other) const;
  Worker CreatePromotedWorker(const std::string &new_position,
                              double bonus_rate) const;

  bool SaveToFile(const std::string &filename) const;
  bool LoadFromFile(const std::string &filename);
  void WriteToStream(std::ostream &out) const;
  bool ReadFromStream(std::istream &in);

  void AllocateAndSortMemory() const;

  int GetWorkerId() const { return worker_id_; }
  double GetHourlyRate() const { return hourly_rate_; }
  int GetCompletedTasks() const { return completed_tasks_; }
  double GetAllocatedBudget() const { return allocated_budget_; }
  int GetProductivityScore() const { return productivity_score_; }
  int GetEmployeeCode() const { return employee_code_; }
  const std::string &GetDepartmentRef() const { return department_ref_; }

  void SetHourlyRate(double rate) { hourly_rate_ = rate; }
  void SetProductivityScore(int score) { productivity_score_ = score; }

  static int GetTotalWorkersCount() { return total_workers_count_; }
  static void PrintTotalWorkersCount();

  void PrintInfo() const;
  void PublicWorkReport() const;

  int GetAccessLevel() const { return access_level_; }
  double GetBaseAllowance() const { return base_allowance_; }
  const std::string &GetClearanceStatus() const { return clearance_status_; }

protected:
  int access_level_;
  double base_allowance_;
  std::string clearance_status_;

  void ProtectedSecurityCheck() const;
  double CalculateInternalBonus(double factor) const;
  void UpdateClearance(int new_level, const std::string &status);

private:
  static int total_workers_count_;

  const int employee_code_;
  const std::string &department_ref_;

  int worker_id_;
  double hourly_rate_;
  int completed_tasks_;
  double allocated_budget_;
  int productivity_score_;

  void PrivateAuditLog(const std::string &action) const;
  bool ValidateConfidentialCredentials() const;
  double ComputeTaxDeductions(double amount) const;
};

class Project {
public:
  std::string title;
  std::string client_name;
  int deadline_days;

  Project();
  Project(int id, const std::string &proj_title, const std::string &client,
          int days, double total_budget, double spent_budget, int resources,
          const Worker &lead, int code, const ProjectModule &module);
  Project(int id, const std::string &proj_title, const std::string &client,
          int days, double total_budget, double spent_budget, int resources,
          const Worker &lead);
  Project(const Project &other);
  Project &operator=(const Project &other);
  ~Project();

  double GetRemainingBudget() const;
  void AddResources(int count);
  void AddResources(int count, double additional_cost);
  bool AssignBudgetToLead(double amount);
  void MergeProject(const Project &other);
  Project CreateSubproject(const std::string &sub_title,
                           double sub_budget) const;
  bool ExecuteSprint(int tasks_to_complete, double sprint_cost);

  void DeliverCurrentModule(int progress);

  bool SaveToFile(const std::string &filename) const;
  bool LoadFromFile(const std::string &filename);
  void WriteToStream(std::ostream &out) const;
  bool ReadFromStream(std::istream &in);

  void AllocateAndSortMemory() const;

  int GetProjectId() const { return project_id_; }
  double GetTotalBudget() const { return total_budget_; }
  double GetSpentBudget() const { return spent_budget_; }
  int GetRequiredResourcesCount() const { return required_resources_count_; }
  int GetProjectCode() const { return project_code_; }
  const Worker &GetLeadWorker() const { return lead_worker_; }
  Worker &GetLeadWorker() { return lead_worker_; }
  const ProjectModule &GetModule() const { return module_; }
  ProjectModule &GetModule() { return module_; }

  void SetLeadWorker(const Worker &lead) { lead_worker_ = lead; }

  static int GetTotalProjectsCount() { return total_projects_count_; }
  static void PrintTotalProjectsCount();

  void PrintInfo() const;

private:
  static int total_projects_count_;

  const int project_code_;

  int project_id_;
  double total_budget_;
  double spent_budget_;
  int required_resources_count_;
  Worker lead_worker_;
  ProjectModule module_;
};

class Department {
public:
  Department();
  Department(const std::string &name, Worker *manager);
  Department(const Department &other);
  Department &operator=(const Department &other);
  ~Department();

  void AssignManager(Worker *manager);
  void ConductDepartmentSprint(int tasks, double budget_allocation);
  void PrintInfo() const;

  const std::string &GetDepartmentName() const { return department_name_; }
  Worker *GetManager() const { return manager_; }

private:
  std::string department_name_;
  Worker *manager_;
};

class TaskAssignment {
public:
  TaskAssignment();
  TaskAssignment(Worker *dev, Worker *rev, Project *proj,
                 const std::string &title, int hours, double cost);
  TaskAssignment(const TaskAssignment &other);
  TaskAssignment &operator=(const TaskAssignment &other);
  ~TaskAssignment();

  bool ExecuteAssignment();
  void PrintInfo() const;

  bool IsCompleted() const { return is_completed_; }
  const std::string &GetTaskTitle() const { return task_title_; }

private:
  Worker *developer_;
  Worker *reviewer_;
  Project *project_;
  std::string task_title_;
  int planned_hours_;
  double task_cost_;
  bool is_completed_;
};

void CalculateWorkerEfficiency(Worker worker);
void CalculateWorkerEfficiency(const Worker *worker);
Worker ProcessWorkerBonusAndElevation(Worker worker, double extra_budget,
                                      int extra_tasks);

#endif
