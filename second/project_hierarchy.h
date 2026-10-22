#ifndef PROJECT_HIERARCHY_H_
#define PROJECT_HIERARCHY_H_

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

#include "project_management.h"

class SoftwareDeveloper : public Worker {
 public:
  using Worker::CompleteTasks;

  SoftwareDeveloper()
      : Worker(),
        primary_programming_language_("C++"),
        preferred_ide_("CLion / Neovim"),
        git_repositories_count_(1),
        resolved_tickets_count_(0),
        code_test_coverage_percent_(80.0),
        knows_design_patterns_(true),
        total_code_commits_(0),
        active_git_branch_("main") {
    std::cout << "[SoftwareDeveloper::Конструктор за замовчуванням] Створено розробника: "
              << Worker::name << " (мова: " << primary_programming_language_ << ")\n";
  }

  SoftwareDeveloper(int id, const std::string& name, const std::string& position,
                    int exp_years, double rate, const std::string& primary_lang,
                    const std::string& ide, int repos, int tickets,
                    double coverage, bool patterns, int commits,
                    const std::string& branch)
      : Worker(id, name, position, exp_years, rate),
        primary_programming_language_(primary_lang),
        preferred_ide_(ide),
        git_repositories_count_(repos),
        resolved_tickets_count_(tickets),
        code_test_coverage_percent_(coverage),
        knows_design_patterns_(patterns),
        total_code_commits_(commits),
        active_git_branch_(branch) {
    std::cout << "[SoftwareDeveloper::Конструктор з параметрами] Створено розробника: "
              << Worker::name << " | Стек: " << primary_programming_language_
              << " | Покриття: " << code_test_coverage_percent_ << "%\n";
  }

  SoftwareDeveloper(const SoftwareDeveloper& other)
      : Worker(other),
        primary_programming_language_(other.primary_programming_language_),
        preferred_ide_(other.preferred_ide_),
        git_repositories_count_(other.git_repositories_count_),
        resolved_tickets_count_(other.resolved_tickets_count_),
        code_test_coverage_percent_(other.code_test_coverage_percent_),
        knows_design_patterns_(other.knows_design_patterns_),
        total_code_commits_(other.total_code_commits_),
        active_git_branch_(other.active_git_branch_) {
    std::cout << "[SoftwareDeveloper::Конструктор копіювання] Скопійовано розробника: "
              << Worker::name << "\n";
  }

  SoftwareDeveloper& operator=(const SoftwareDeveloper& other) {
    if (this != &other) {
      Worker::operator=(other);
      primary_programming_language_ = other.primary_programming_language_;
      preferred_ide_ = other.preferred_ide_;
      git_repositories_count_ = other.git_repositories_count_;
      resolved_tickets_count_ = other.resolved_tickets_count_;
      code_test_coverage_percent_ = other.code_test_coverage_percent_;
      knows_design_patterns_ = other.knows_design_patterns_;
      total_code_commits_ = other.total_code_commits_;
      active_git_branch_ = other.active_git_branch_;
    }
    return *this;
  }

  virtual ~SoftwareDeveloper() {
    std::cout << "[SoftwareDeveloper::Деструктор] Вихід з блоку / знищення розробника: "
              << Worker::name << " (мова: " << primary_programming_language_ << ")\n";
  }

  void WriteCode(int lines_count) {
    total_code_commits_ += (lines_count / 100) + 1;
    resolved_tickets_count_ += 1;
    std::cout << "[SoftwareDeveloper::WriteCode] Розробник " << Worker::name
              << " написав " << lines_count << " рядків коду на "
              << primary_programming_language_ << ". Всього коммітів: "
              << total_code_commits_ << "\n";
  }

  void RunUnitTests(int test_cases) {
    double boost = test_cases * 0.15;
    code_test_coverage_percent_ = std::min(100.0, code_test_coverage_percent_ + boost);
    std::cout << "[SoftwareDeveloper::RunUnitTests] Виконано " << test_cases
              << " unit-тестів у середовищі " << preferred_ide_
              << ". Нове тестове покриття: " << std::fixed << std::setprecision(1)
              << code_test_coverage_percent_ << "%\n";
  }

  void CommitCode(const std::string& commit_message) {
    total_code_commits_++;
    std::cout << "[SoftwareDeveloper::CommitCode] [Гілка: " << active_git_branch_
              << "] Комміт #" << total_code_commits_ << ": \"" << commit_message
              << "\" успішно відправлено!\n";
  }

  void DemonstrateAccessControl() {
    std::cout << "\n--- Демонстрація доступу в SoftwareDeveloper (public наслідування) ---\n";
    std::cout << "1) Доступ до public-поля базового класу Worker::name: "
              << Worker::name << "\n";
    std::cout << "   Виклик public-методу базового класу Worker::CalculateSalary(160): "
              << Worker::CalculateSalary(160) << " $\n";
    std::cout << "2) Доступ до protected-поля Worker::access_level_: "
              << Worker::access_level_ << "\n";
    std::cout << "   Виклик protected-методу Worker::ProtectedSecurityCheck(): ";
    Worker::ProtectedSecurityCheck();
    std::cout << "   Виклик protected-методу Worker::CalculateInternalBonus(1.2): ";
    Worker::CalculateInternalBonus(1.2);
    std::cout << "3) Private-члени Worker (worker_id_, PrivateAuditLog) недоступні напряму з похідного класу.\n"
              << "   Доступ можливий лише через public/protected інтерфейс (GetWorkerId(): "
              << Worker::GetWorkerId() << ").\n";
  }

  void PrintDeveloperDetails() const {
    Worker::PrintInfo();
    std::cout << "  [SoftwareDeveloper]\n"
              << "    Основна мова:         " << primary_programming_language_ << "\n"
              << "    IDE:                  " << preferred_ide_ << "\n"
              << "    Кількість репозиторіїв: " << git_repositories_count_ << "\n"
              << "    Вирішено тікетів:     " << resolved_tickets_count_ << "\n"
              << "    Покриття тестами:     " << code_test_coverage_percent_ << "%\n"
              << "    Знання патернів:      " << (knows_design_patterns_ ? "Так" : "Ні") << "\n"
              << "    Всього коммітів:      " << total_code_commits_ << "\n"
              << "    Поточна гілка git:    " << active_git_branch_ << "\n";
  }

  const std::string& GetPrimaryLanguage() const { return primary_programming_language_; }
  const std::string& GetPreferredIde() const { return preferred_ide_; }
  int GetGitRepositoriesCount() const { return git_repositories_count_; }
  int GetResolvedTicketsCount() const { return resolved_tickets_count_; }
  double GetCodeCoverage() const { return code_test_coverage_percent_; }
  bool GetKnowsDesignPatterns() const { return knows_design_patterns_; }
  int GetTotalCommits() const { return total_code_commits_; }
  const std::string& GetActiveGitBranch() const { return active_git_branch_; }

 private:
  std::string primary_programming_language_;
  std::string preferred_ide_;
  int git_repositories_count_;
  int resolved_tickets_count_;
  double code_test_coverage_percent_;
  bool knows_design_patterns_;
  int total_code_commits_;
  std::string active_git_branch_;
};

class ProjectSupervisor : protected Worker {
 public:
  using Worker::PrintInfo;

  ProjectSupervisor()
      : Worker(),
        supervised_sector_("Архітектурний нагляд"),
        supervised_teams_count_(2),
        monthly_supervision_budget_(35000.0),
        inspection_frequency_days_(14),
        performance_target_kpi_(92.5),
        has_executive_signing_authority_(true),
        approved_milestones_count_(0),
        reporting_office_("Центральний офіс") {
    std::cout << "[ProjectSupervisor::Конструктор за замовчуванням] Створено супервайзера: "
              << Worker::name << " (сектор: " << supervised_sector_ << ")\n";
  }

  ProjectSupervisor(int id, const std::string& name, const std::string& position,
                    int exp_years, double rate, const std::string& sector,
                    int teams, double budget, int freq_days, double kpi,
                    bool signing_auth, int milestones, const std::string& office)
      : Worker(id, name, position, exp_years, rate),
        supervised_sector_(sector),
        supervised_teams_count_(teams),
        monthly_supervision_budget_(budget),
        inspection_frequency_days_(freq_days),
        performance_target_kpi_(kpi),
        has_executive_signing_authority_(signing_auth),
        approved_milestones_count_(milestones),
        reporting_office_(office) {
    std::cout << "[ProjectSupervisor::Конструктор з параметрами] Створено супервайзера: "
              << Worker::name << " | Сектор: " << supervised_sector_
              << " | Команд: " << supervised_teams_count_ << "\n";
  }

  ProjectSupervisor(const ProjectSupervisor& other)
      : Worker(other),
        supervised_sector_(other.supervised_sector_),
        supervised_teams_count_(other.supervised_teams_count_),
        monthly_supervision_budget_(other.monthly_supervision_budget_),
        inspection_frequency_days_(other.inspection_frequency_days_),
        performance_target_kpi_(other.performance_target_kpi_),
        has_executive_signing_authority_(other.has_executive_signing_authority_),
        approved_milestones_count_(other.approved_milestones_count_),
        reporting_office_(other.reporting_office_) {
    std::cout << "[ProjectSupervisor::Конструктор копіювання] Скопійовано супервайзера: "
              << Worker::name << "\n";
  }

  ProjectSupervisor& operator=(const ProjectSupervisor& other) {
    if (this != &other) {
      Worker::operator=(other);
      supervised_sector_ = other.supervised_sector_;
      supervised_teams_count_ = other.supervised_teams_count_;
      monthly_supervision_budget_ = other.monthly_supervision_budget_;
      inspection_frequency_days_ = other.inspection_frequency_days_;
      performance_target_kpi_ = other.performance_target_kpi_;
      has_executive_signing_authority_ = other.has_executive_signing_authority_;
      approved_milestones_count_ = other.approved_milestones_count_;
      reporting_office_ = other.reporting_office_;
    }
    return *this;
  }

  virtual ~ProjectSupervisor() {
    std::cout << "[ProjectSupervisor::Деструктор] Вихід з блоку / знищення супервайзера: "
              << Worker::name << " (сектор: " << supervised_sector_ << ")\n";
  }

  void ConductSupervisorInspection() {
    std::cout << "[ProjectSupervisor::ConductSupervisorInspection] Проведення нагляду сектору '"
              << supervised_sector_ << "' під керівництвом " << Worker::name << "...\n";
    Worker::ProtectedSecurityCheck();
    double internal_allowance = Worker::CalculateInternalBonus(1.4);
    std::cout << "  Виділено бонус за нагляд: " << internal_allowance << " грн.\n";
  }

  void ApproveProjectMilestone(const std::string& milestone_name) {
    approved_milestones_count_++;
    std::cout << "[ProjectSupervisor::ApproveProjectMilestone] Супервайзер "
              << Worker::name << " затвердив віху проєкту: \"" << milestone_name
              << "\". Всього затверджено віх: " << approved_milestones_count_ << "\n";
  }

  void DemonstrateProtectedInheritance() {
    std::cout << "\n--- Демонстрація protected наслідування в ProjectSupervisor ---\n";
    std::cout << "При protected наслідуванні public та protected члени Worker стають protected у ProjectSupervisor.\n";
    std::cout << "Всередині методів супервайзера вони доступні:\n";
    std::cout << "  Worker::name = " << Worker::name << "\n";
    std::cout << "  Worker::access_level_ = " << Worker::access_level_ << "\n";
    std::cout << "  Worker::CalculateSalary(160) = " << Worker::CalculateSalary(160) << " $\n";
    std::cout << "Зовні класу виклик supervisor.CalculateSalary() є заблокованим компілятором!\n";
  }

  void PrintSupervisorInfo() const {
    std::cout << "========================================\n"
              << "Керівник напрямку (ProjectSupervisor - protected наслідування):\n"
              << "  Ім'я керівника:         " << Worker::name << "\n"
              << "  Посада:                 " << Worker::position << "\n"
              << "  Кураторський сектор:    " << supervised_sector_ << "\n"
              << "  Кількість команд:       " << supervised_teams_count_ << "\n"
              << "  Бюджет нагляду:         " << monthly_supervision_budget_ << " грн/міс\n"
              << "  Частота інспекцій:      раз у " << inspection_frequency_days_ << " днів\n"
              << "  Цільовий KPI:           " << performance_target_kpi_ << "%\n"
              << "  Право підпису:          " << (has_executive_signing_authority_ ? "Наявне" : "Відсутнє") << "\n"
              << "  Затверджених віх:       " << approved_milestones_count_ << "\n"
              << "  Офіс звітування:        " << reporting_office_ << "\n"
              << "========================================\n";
  }

  const std::string& GetSupervisedSector() const { return supervised_sector_; }
  int GetSupervisedTeamsCount() const { return supervised_teams_count_; }
  double GetSupervisionBudget() const { return monthly_supervision_budget_; }
  int GetInspectionFrequency() const { return inspection_frequency_days_; }
  double GetTargetKpi() const { return performance_target_kpi_; }
  bool HasSigningAuthority() const { return has_executive_signing_authority_; }
  int GetApprovedMilestonesCount() const { return approved_milestones_count_; }
  const std::string& GetReportingOffice() const { return reporting_office_; }

 protected:
  std::string supervised_sector_;
  int supervised_teams_count_;
  double monthly_supervision_budget_;
  int inspection_frequency_days_;
  double performance_target_kpi_;
  bool has_executive_signing_authority_;
  int approved_milestones_count_;
  std::string reporting_office_;
};

class SecurityAuditor : private Worker {
 public:
  using Worker::name;
  using Worker::CalculateSalary;
  using Worker::PrintInfo;

  SecurityAuditor()
      : Worker(),
        audit_certificate_id_("CERT-SEC-001"),
        audit_standard_iso_("ISO/IEC 27001"),
        security_vulnerabilities_found_(0),
        compliance_rating_(98.5),
        has_penetration_test_license_(true),
        audited_systems_count_(0),
        audit_budget_limit_(50000.0),
        audit_agency_name_("CyberSecurity Guard UA") {
    std::cout << "[SecurityAuditor::Конструктор за замовчуванням] Створено аудитора безпеки: "
              << Worker::name << " (сертифікат: " << audit_certificate_id_ << ")\n";
  }

  SecurityAuditor(int id, const std::string& name, const std::string& position,
                  int exp_years, double rate, const std::string& cert_id,
                  const std::string& iso_std, int vulns, double comp_rating,
                  bool pen_test, int audited_sys, double audit_budget,
                  const std::string& agency)
      : Worker(id, name, position, exp_years, rate),
        audit_certificate_id_(cert_id),
        audit_standard_iso_(iso_std),
        security_vulnerabilities_found_(vulns),
        compliance_rating_(comp_rating),
        has_penetration_test_license_(pen_test),
        audited_systems_count_(audited_sys),
        audit_budget_limit_(audit_budget),
        audit_agency_name_(agency) {
    std::cout << "[SecurityAuditor::Конструктор з параметрами] Створено аудитора безпеки: "
              << Worker::name << " | Агентство: " << audit_agency_name_
              << " | Стандарт: " << audit_standard_iso_ << "\n";
  }

  SecurityAuditor(const SecurityAuditor& other)
      : Worker(other),
        audit_certificate_id_(other.audit_certificate_id_),
        audit_standard_iso_(other.audit_standard_iso_),
        security_vulnerabilities_found_(other.security_vulnerabilities_found_),
        compliance_rating_(other.compliance_rating_),
        has_penetration_test_license_(other.has_penetration_test_license_),
        audited_systems_count_(other.audited_systems_count_),
        audit_budget_limit_(other.audit_budget_limit_),
        audit_agency_name_(other.audit_agency_name_) {
    std::cout << "[SecurityAuditor::Конструктор копіювання] Скопійовано аудитора безпеки: "
              << Worker::name << "\n";
  }

  SecurityAuditor& operator=(const SecurityAuditor& other) {
    if (this != &other) {
      Worker::operator=(other);
      audit_certificate_id_ = other.audit_certificate_id_;
      audit_standard_iso_ = other.audit_standard_iso_;
      security_vulnerabilities_found_ = other.security_vulnerabilities_found_;
      compliance_rating_ = other.compliance_rating_;
      has_penetration_test_license_ = other.has_penetration_test_license_;
      audited_systems_count_ = other.audited_systems_count_;
      audit_budget_limit_ = other.audit_budget_limit_;
      audit_agency_name_ = other.audit_agency_name_;
    }
    return *this;
  }

  virtual ~SecurityAuditor() {
    std::cout << "[SecurityAuditor::Деструктор] Вихід з блоку / знищення аудитора безпеки: "
              << Worker::name << " (" << audit_agency_name_ << ")\n";
  }

  void PerformFullSystemAudit(Project* proj, SoftwareDeveloper* dev, ProjectSupervisor* supervisor) {
    std::cout << "\n>>> [SecurityAuditor::PerformFullSystemAudit] Початок комплексного аудиту системи <<<\n";
    std::cout << "Аудитор: " << Worker::name << " (Сертифікат: " << audit_certificate_id_
              << ", Стандарт: " << audit_standard_iso_ << ")\n";

    Worker::ProtectedSecurityCheck();

    if (dev) {
      std::cout << "1) Аудит розробника (" << dev->name << "):\n";
      std::cout << "   - Мова коду: " << dev->GetPrimaryLanguage() << "\n";
      std::cout << "   - Покриття тестами: " << dev->GetCodeCoverage() << "%\n";
      std::cout << "   - Виклик тестового прогону для аудиту...\n   ";
      dev->RunUnitTests(15);
    }

    if (proj) {
      std::cout << "2) Аудит проєкту (\"" << proj->title << "\"):\n";
      std::cout << "   - Залишок бюджету: " << proj->GetRemainingBudget() << " грн\n";
      std::cout << "   - Витрачено коштів: " << proj->GetSpentBudget() << " грн\n";
      std::cout << "   - Перевірка виконання модуля проєкту...\n   ";
      proj->DeliverCurrentModule(20);
    }

    if (supervisor) {
      std::cout << "3) Аудит сектору нагляду (\"" << supervisor->GetSupervisedSector() << "\"):\n";
      std::cout << "   - Кількість команд під наглядом: " << supervisor->GetSupervisedTeamsCount() << "\n";
      std::cout << "   - Затверджених віх: " << supervisor->GetApprovedMilestonesCount() << "\n";
    }

    audited_systems_count_++;
    compliance_rating_ = std::min(100.0, compliance_rating_ + 0.5);
    std::cout << ">>> Аудит успішно завершено! Перевірено систем: " << audited_systems_count_
              << ", Підсумковий рейтинг комплаєнсу: " << compliance_rating_ << "% <<<\n\n";
  }

  void DemonstratePrivateInheritanceAccess() {
    std::cout << "\n--- Демонстрація private наслідування в SecurityAuditor ---\n";
    std::cout << "У SecurityAuditor всі успадковані члени Worker стали приватними за замовчуванням.\n";
    std::cout << "Завдяки директивам using у секції public:\n";
    std::cout << "Клієнтський код ззовні може викликати auditor.CalculateSalary(160): "
              << CalculateSalary(160) << " $\n";
    std::cout << "А також читати auditor.name: " << name << "\n";
    std::cout << "А всередині методів SecurityAuditor доступні поля через оператор :: -> Worker::access_level_ = "
              << Worker::access_level_ << "\n";
  }

  void PrintAuditSummary() const {
    std::cout << "========================================\n"
              << "Аудитор інформаційної безпеки (SecurityAuditor):\n"
              << "  Ім'я аудитора:          " << Worker::name << "\n"
              << "  Сертифікат ID:          " << audit_certificate_id_ << "\n"
              << "  Стандарт безпеки:       " << audit_standard_iso_ << "\n"
              << "  Виявлено вразливостей:  " << security_vulnerabilities_found_ << "\n"
              << "  Рейтинг відповідності:  " << compliance_rating_ << "%\n"
              << "  Ліцензія пентестів:     " << (has_penetration_test_license_ ? "Активна" : "Немає") << "\n"
              << "  Проаудійовано систем:   " << audited_systems_count_ << "\n"
              << "  Ліміт бюджету аудиту:   " << audit_budget_limit_ << " грн\n"
              << "  Агентство:              " << audit_agency_name_ << "\n"
              << "========================================\n";
  }

  const std::string& GetCertificateId() const { return audit_certificate_id_; }
  const std::string& GetAuditStandard() const { return audit_standard_iso_; }
  int GetVulnerabilitiesFound() const { return security_vulnerabilities_found_; }
  double GetComplianceRating() const { return compliance_rating_; }
  bool HasPenTestLicense() const { return has_penetration_test_license_; }
  int GetAuditedSystemsCount() const { return audited_systems_count_; }
  double GetAuditBudgetLimit() const { return audit_budget_limit_; }
  const std::string& GetAuditAgencyName() const { return audit_agency_name_; }

 private:
  std::string audit_certificate_id_;
  std::string audit_standard_iso_;
  int security_vulnerabilities_found_;
  double compliance_rating_;
  bool has_penetration_test_license_;
  int audited_systems_count_;
  double audit_budget_limit_;
  std::string audit_agency_name_;
};

class SoftwareArchitect : public SoftwareDeveloper {
 public:
  SoftwareArchitect()
      : SoftwareDeveloper(),
        architectural_pattern_("Clean Architecture / Microservices"),
        cloud_platform_("AWS & Kubernetes"),
        designed_systems_count_(5),
        system_scalability_level_(9),
        architecture_budget_(75000.0),
        has_cloud_certification_(true),
        microservices_count_(12),
        system_blueprint_id_("ARCH-BLPRNT-2026") {
    std::cout << "[SoftwareArchitect::Конструктор за замовчуванням] Створено архітектора: "
              << Worker::name << "\n";
  }

  SoftwareArchitect(int id, const std::string& name, const std::string& position,
                    int exp_years, double rate, const std::string& primary_lang,
                    const std::string& ide, int repos, int tickets,
                    double coverage, bool patterns, int commits,
                    const std::string& branch, const std::string& pattern,
                    const std::string& cloud, int systems_count, int scalability,
                    double arch_budget, bool cloud_cert, int microservices,
                    const std::string& blueprint_id)
      : SoftwareDeveloper(id, name, position, exp_years, rate, primary_lang, ide,
                          repos, tickets, coverage, patterns, commits, branch),
        architectural_pattern_(pattern),
        cloud_platform_(cloud),
        designed_systems_count_(systems_count),
        system_scalability_level_(scalability),
        architecture_budget_(arch_budget),
        has_cloud_certification_(cloud_cert),
        microservices_count_(microservices),
        system_blueprint_id_(blueprint_id) {
    std::cout << "[SoftwareArchitect::Конструктор з параметрами] Створено архітектора: "
              << Worker::name << " | Патерн: " << architectural_pattern_
              << " | Хмара: " << cloud_platform_ << "\n";
  }

  SoftwareArchitect(const SoftwareArchitect& other)
      : SoftwareDeveloper(other),
        architectural_pattern_(other.architectural_pattern_),
        cloud_platform_(other.cloud_platform_),
        designed_systems_count_(other.designed_systems_count_),
        system_scalability_level_(other.system_scalability_level_),
        architecture_budget_(other.architecture_budget_),
        has_cloud_certification_(other.has_cloud_certification_),
        microservices_count_(other.microservices_count_),
        system_blueprint_id_(other.system_blueprint_id_) {
    std::cout << "[SoftwareArchitect::Конструктор копіювання] Скопійовано архітектора: "
              << Worker::name << "\n";
  }

  SoftwareArchitect& operator=(const SoftwareArchitect& other) {
    if (this != &other) {
      SoftwareDeveloper::operator=(other);
      architectural_pattern_ = other.architectural_pattern_;
      cloud_platform_ = other.cloud_platform_;
      designed_systems_count_ = other.designed_systems_count_;
      system_scalability_level_ = other.system_scalability_level_;
      architecture_budget_ = other.architecture_budget_;
      has_cloud_certification_ = other.has_cloud_certification_;
      microservices_count_ = other.microservices_count_;
      system_blueprint_id_ = other.system_blueprint_id_;
    }
    return *this;
  }

  virtual ~SoftwareArchitect() {
    std::cout << "[SoftwareArchitect::Деструктор] Вихід з блоку / знищення архітектора: "
              << Worker::name << " (патерн: " << architectural_pattern_ << ")\n";
  }

  void DesignSystemArchitecture(const std::string& system_name) {
    designed_systems_count_++;
    std::cout << "[SoftwareArchitect::DesignSystemArchitecture] Архітектор "
              << Worker::name << " спроєктував архітектуру для \"" << system_name
              << "\" з патерном " << architectural_pattern_
              << " та розгортанням у " << cloud_platform_ << ".\n";
  }

  void OptimizeCloudInfrastructure() {
    std::cout << "[SoftwareArchitect::OptimizeCloudInfrastructure] Оптимізація інфраструктури хмари "
              << cloud_platform_ << " для " << microservices_count_ << " мікросервісів.\n";
  }

  void PrintArchitectDetails() const {
    SoftwareDeveloper::PrintDeveloperDetails();
    std::cout << "  [SoftwareArchitect]\n"
              << "    Архітектурний патерн: " << architectural_pattern_ << "\n"
              << "    Хмарна платформа:     " << cloud_platform_ << "\n"
              << "    Спроєктовано систем:  " << designed_systems_count_ << "\n"
              << "    Рівень масштабування: " << system_scalability_level_ << "/10\n"
              << "    Бюджет архітектури:   " << architecture_budget_ << " грн\n"
              << "    Сертифікація хмари:   " << (has_cloud_certification_ ? "AWS Certified" : "Ні") << "\n"
              << "    Мікросервісів:        " << microservices_count_ << "\n"
              << "    Код креслення (ID):   " << system_blueprint_id_ << "\n";
  }

  const std::string& GetArchitecturalPattern() const { return architectural_pattern_; }
  const std::string& GetCloudPlatform() const { return cloud_platform_; }
  int GetDesignedSystemsCount() const { return designed_systems_count_; }
  int GetScalabilityLevel() const { return system_scalability_level_; }
  double GetArchitectureBudget() const { return architecture_budget_; }
  bool HasCloudCertification() const { return has_cloud_certification_; }
  int GetMicroservicesCount() const { return microservices_count_; }
  const std::string& GetBlueprintId() const { return system_blueprint_id_; }

 protected:
  std::string architectural_pattern_;
  std::string cloud_platform_;
  int designed_systems_count_;
  int system_scalability_level_;
  double architecture_budget_;
  bool has_cloud_certification_;
  int microservices_count_;
  std::string system_blueprint_id_;
};

class ProjectConsultant {
 public:
  ProjectConsultant()
      : consultant_firm_("McKinsey & Tech Advisory"),
        domain_specialization_("IT Transformation & Risk Management"),
        consulting_experience_years_(8),
        advisory_hourly_rate_(95.0),
        completed_consultations_(24),
        estimated_roi_boost_(35.0),
        is_external_advisor_(true),
        strategic_roadmap_id_("ROADMAP-STRAT-2026") {
    std::cout << "[ProjectConsultant::Конструктор за замовчуванням] Створено консультанта від "
              << consultant_firm_ << "\n";
  }

  ProjectConsultant(const std::string& firm, const std::string& domain,
                    int exp_years, double fee_rate, int consultations,
                    double roi_boost, bool is_external,
                    const std::string& roadmap_id)
      : consultant_firm_(firm),
        domain_specialization_(domain),
        consulting_experience_years_(exp_years),
        advisory_hourly_rate_(fee_rate),
        completed_consultations_(consultations),
        estimated_roi_boost_(roi_boost),
        is_external_advisor_(is_external),
        strategic_roadmap_id_(roadmap_id) {
    std::cout << "[ProjectConsultant::Конструктор з параметрами] Створено консультанта: "
              << consultant_firm_ << " | Спеціалізація: " << domain_specialization_ << "\n";
  }

  ProjectConsultant(const ProjectConsultant& other)
      : consultant_firm_(other.consultant_firm_),
        domain_specialization_(other.domain_specialization_),
        consulting_experience_years_(other.consulting_experience_years_),
        advisory_hourly_rate_(other.advisory_hourly_rate_),
        completed_consultations_(other.completed_consultations_),
        estimated_roi_boost_(other.estimated_roi_boost_),
        is_external_advisor_(other.is_external_advisor_),
        strategic_roadmap_id_(other.strategic_roadmap_id_) {
    std::cout << "[ProjectConsultant::Конструктор копіювання] Скопійовано консультанта: "
              << consultant_firm_ << "\n";
  }

  ProjectConsultant& operator=(const ProjectConsultant& other) {
    if (this != &other) {
      consultant_firm_ = other.consultant_firm_;
      domain_specialization_ = other.domain_specialization_;
      consulting_experience_years_ = other.consulting_experience_years_;
      advisory_hourly_rate_ = other.advisory_hourly_rate_;
      completed_consultations_ = other.completed_consultations_;
      estimated_roi_boost_ = other.estimated_roi_boost_;
      is_external_advisor_ = other.is_external_advisor_;
      strategic_roadmap_id_ = other.strategic_roadmap_id_;
    }
    return *this;
  }

  virtual ~ProjectConsultant() {
    std::cout << "[ProjectConsultant::Деструктор] Вихід з блоку / знищення консультанта: "
              << consultant_firm_ << " (" << domain_specialization_ << ")\n";
  }

  void ProvideStrategicGuidance(Project* proj) {
    completed_consultations_++;
    std::cout << "[ProjectConsultant::ProvideStrategicGuidance] Консультант з "
              << consultant_firm_ << " надає стратегічні рекомендації для проєкту \""
              << (proj ? proj->title : "Невизначений") << "\". Очікуване зростання ROI: +"
              << estimated_roi_boost_ << "%\n";
  }

  double CalculateConsultingFee(int hours) const {
    return hours * advisory_hourly_rate_;
  }

  void PrintConsultantInfo() const {
    std::cout << "========================================\n"
              << "Консультант проєкту (ProjectConsultant):\n"
              << "  Консалтингова фірма:    " << consultant_firm_ << "\n"
              << "  Спеціалізація:          " << domain_specialization_ << "\n"
              << "  Досвід консультування:  " << consulting_experience_years_ << " років\n"
              << "  Годинна ставка:         " << advisory_hourly_rate_ << " $/год\n"
              << "  Проведено консультацій: " << completed_consultations_ << "\n"
              << "  Прогнозований ROI:      +" << estimated_roi_boost_ << "%\n"
              << "  Тип експерта:           " << (is_external_advisor_ ? "Зовнішній радник" : "Внутрішній") << "\n"
              << "  Дорожня карта (ID):     " << strategic_roadmap_id_ << "\n"
              << "========================================\n";
  }

  const std::string& GetConsultantFirm() const { return consultant_firm_; }
  const std::string& GetDomainSpecialization() const { return domain_specialization_; }
  int GetConsultingExperienceYears() const { return consulting_experience_years_; }
  double GetAdvisoryHourlyRate() const { return advisory_hourly_rate_; }
  int GetCompletedConsultations() const { return completed_consultations_; }
  double GetEstimatedRoiBoost() const { return estimated_roi_boost_; }
  bool IsExternalAdvisor() const { return is_external_advisor_; }
  const std::string& GetRoadmapId() const { return strategic_roadmap_id_; }

 protected:
  std::string consultant_firm_;
  std::string domain_specialization_;
  int consulting_experience_years_;
  double advisory_hourly_rate_;
  int completed_consultations_;
  double estimated_roi_boost_;
  bool is_external_advisor_;
  std::string strategic_roadmap_id_;
};

class EngineeringDirector : public SoftwareArchitect, public ProjectConsultant {
 public:
  using SoftwareArchitect::RunUnitTests;
  using SoftwareArchitect::PrintDeveloperDetails;
  using ProjectConsultant::PrintConsultantInfo;
  using ProjectConsultant::ProvideStrategicGuidance;

  EngineeringDirector()
      : SoftwareArchitect(),
        ProjectConsultant(),
        directorate_name_("Директорат інженерії та цифрової трансформації"),
        total_subordinates_count_(45),
        annual_department_budget_(1200000.0),
        strategic_goals_set_(10),
        strategic_delivery_rate_(94.0),
        board_member_status_(true),
        managed_projects_count_(6),
        headquarters_location_("Київ / Віддалено") {
    std::cout << "[EngineeringDirector::Конструктор за замовчуванням] Створено директора інженерії: "
              << SoftwareArchitect::Worker::name << " (" << directorate_name_ << ")\n";
  }

  EngineeringDirector(int id, const std::string& name, const std::string& position,
                      int exp_years, double rate, const std::string& primary_lang,
                      const std::string& ide, int repos, int tickets,
                      double coverage, bool patterns, int commits,
                      const std::string& branch, const std::string& pattern,
                      const std::string& cloud, int systems_count,
                      int scalability, double arch_budget, bool cloud_cert,
                      int microservices, const std::string& blueprint_id,
                      const std::string& firm, const std::string& domain,
                      int consult_exp, double fee_rate, int consultations,
                      double roi_boost, bool is_external,
                      const std::string& roadmap_id,
                      const std::string& directorate, int subordinates,
                      double annual_budget, int goals_set, double delivery_rate,
                      bool board_member, int managed_projects,
                      const std::string& hq_location)
      : SoftwareArchitect(id, name, position, exp_years, rate, primary_lang, ide,
                          repos, tickets, coverage, patterns, commits, branch,
                          pattern, cloud, systems_count, scalability, arch_budget,
                          cloud_cert, microservices, blueprint_id),
        ProjectConsultant(firm, domain, consult_exp, fee_rate, consultations,
                          roi_boost, is_external, roadmap_id),
        directorate_name_(directorate),
        total_subordinates_count_(subordinates),
        annual_department_budget_(annual_budget),
        strategic_goals_set_(goals_set),
        strategic_delivery_rate_(delivery_rate),
        board_member_status_(board_member),
        managed_projects_count_(managed_projects),
        headquarters_location_(hq_location) {
    std::cout << "[EngineeringDirector::Конструктор з параметрами] Створено директора інженерії: "
              << SoftwareArchitect::Worker::name << " | Директорат: " << directorate_name_
              << " | Підлеглих: " << total_subordinates_count_ << "\n";
  }

  EngineeringDirector(const EngineeringDirector& other)
      : SoftwareArchitect(other),
        ProjectConsultant(other),
        directorate_name_(other.directorate_name_),
        total_subordinates_count_(other.total_subordinates_count_),
        annual_department_budget_(other.annual_department_budget_),
        strategic_goals_set_(other.strategic_goals_set_),
        strategic_delivery_rate_(other.strategic_delivery_rate_),
        board_member_status_(other.board_member_status_),
        managed_projects_count_(other.managed_projects_count_),
        headquarters_location_(other.headquarters_location_) {
    std::cout << "[EngineeringDirector::Конструктор копіювання] Скопійовано директора інженерії: "
              << SoftwareArchitect::Worker::name << "\n";
  }

  EngineeringDirector& operator=(const EngineeringDirector& other) {
    if (this != &other) {
      SoftwareArchitect::operator=(other);
      ProjectConsultant::operator=(other);
      directorate_name_ = other.directorate_name_;
      total_subordinates_count_ = other.total_subordinates_count_;
      annual_department_budget_ = other.annual_department_budget_;
      strategic_goals_set_ = other.strategic_goals_set_;
      strategic_delivery_rate_ = other.strategic_delivery_rate_;
      board_member_status_ = other.board_member_status_;
      managed_projects_count_ = other.managed_projects_count_;
      headquarters_location_ = other.headquarters_location_;
    }
    return *this;
  }

  virtual ~EngineeringDirector() {
    std::cout << "[EngineeringDirector::Деструктор] Вихід з блоку / знищення директора інженерії: "
              << SoftwareArchitect::Worker::name << " (" << directorate_name_ << ")\n";
  }

  void ConductExecutiveReview(Project* proj) {
    std::cout << "\n>>> [EngineeringDirector::ConductExecutiveReview] Директор "
              << SoftwareArchitect::Worker::name << " проводить виконавчий перегляд проєкту...\n";
    SoftwareArchitect::OptimizeCloudInfrastructure();
    ProjectConsultant::ProvideStrategicGuidance(proj);
    std::cout << "Оцінка успішності доставки: " << strategic_delivery_rate_
              << "%. Загальна кількість підлеглих інженерів: "
              << total_subordinates_count_ << "\n\n";
  }

  void AllocateStrategicBudget(double amount) {
    annual_department_budget_ += amount;
    std::cout << "[EngineeringDirector::AllocateStrategicBudget] Виділено додатковий стратегічний бюджет: "
              << amount << " грн. Загальний річний бюджет: "
              << annual_department_budget_ << " грн.\n";
  }

  void PrintDirectorSummary() const {
    std::cout << "====================================================\n"
              << "ДИРЕКТОР ІНЖЕНЕРІЇ (EngineeringDirector - Множинне наслідування):\n"
              << "  Ім'я керівника:         " << SoftwareArchitect::Worker::name << "\n"
              << "  Директорат:             " << directorate_name_ << "\n"
              << "  Кількість підлеглих:    " << total_subordinates_count_ << "\n"
              << "  Річний бюджет:          " << annual_department_budget_ << " грн\n"
              << "  Стратегічних цілей:     " << strategic_goals_set_ << "\n"
              << "  Показник доставки:      " << strategic_delivery_rate_ << "%\n"
              << "  Член ради директорів:   " << (board_member_status_ ? "Так" : "Ні") << "\n"
              << "  Кількість проєктів:     " << managed_projects_count_ << "\n"
              << "  Локація штаб-квартири:  " << headquarters_location_ << "\n"
              << "--- Дані технічного архітектора (гілка SoftwareArchitect) ---\n"
              << "  Архітектурний патерн:   " << architectural_pattern_ << "\n"
              << "  Хмарна платформа:       " << cloud_platform_ << "\n"
              << "  Покриття тестами коду:  " << GetCodeCoverage() << "%\n"
              << "--- Дані стратегічного консультанта (гілка ProjectConsultant) ---\n"
              << "  Консалтингова фірма:    " << consultant_firm_ << "\n"
              << "  Спеціалізація:          " << domain_specialization_ << "\n"
              << "  Годинна ставка радника: " << advisory_hourly_rate_ << " $/год\n"
              << "====================================================\n";
  }

  const std::string& GetDirectorateName() const { return directorate_name_; }
  int GetTotalSubordinatesCount() const { return total_subordinates_count_; }
  double GetAnnualDepartmentBudget() const { return annual_department_budget_; }
  int GetStrategicGoalsSet() const { return strategic_goals_set_; }
  double GetStrategicDeliveryRate() const { return strategic_delivery_rate_; }
  bool IsBoardMember() const { return board_member_status_; }
  int GetManagedProjectsCount() const { return managed_projects_count_; }
  const std::string& GetHeadquartersLocation() const { return headquarters_location_; }

 private:
  std::string directorate_name_;
  int total_subordinates_count_;
  double annual_department_budget_;
  int strategic_goals_set_;
  double strategic_delivery_rate_;
  bool board_member_status_;
  int managed_projects_count_;
  std::string headquarters_location_;
};

#endif
