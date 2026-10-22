#ifndef PERSONNEL_SYSTEM_H_
#define PERSONNEL_SYSTEM_H_

#include <array>
#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class PersonnelException : public std::runtime_error {
 public:
  explicit PersonnelException(const std::string& message);
};

class ValidationException : public PersonnelException {
 public:
  explicit ValidationException(const std::string& message);
};

class DuplicateIdException : public PersonnelException {
 public:
  explicit DuplicateIdException(const std::string& message);
};

class CapacityException : public PersonnelException {
 public:
  explicit CapacityException(const std::string& message);
};

class RecordNotFoundException : public PersonnelException {
 public:
  explicit RecordNotFoundException(const std::string& message);
};

class FileException : public PersonnelException {
 public:
  explicit FileException(const std::string& message);
};

class Employee {
 public:
  Employee(int id, const std::string& name, double salary);
  virtual ~Employee();

  int GetId() const;
  const std::string& GetName() const;
  double GetSalary() const;
  void SetSalary(double salary);

  virtual std::string GetType() const = 0;
  virtual void Work() const = 0;
  virtual void Print(std::ostream& out) const;
  virtual void Write(std::ostream& out) const;
  virtual void Read(std::istream& in);
  virtual std::unique_ptr<Employee> Clone() const = 0;

  void PrintShort(std::ostream& out) const;

 protected:
  void ValidateBaseData() const;

 private:
  int id_;
  std::string name_;
  double salary_;
};

class Developer : public Employee {
 public:
  Developer(int id, const std::string& name, double salary,
            const std::string& language, int completed_features);
  ~Developer() override = default;

  std::string GetType() const override;
  void Work() const override;
  void Print(std::ostream& out) const override;
  void Write(std::ostream& out) const override;
  void Read(std::istream& in) override;
  std::unique_ptr<Employee> Clone() const override;

 private:
  std::string language_;
  int completed_features_;
};

class Tester : public Employee {
 public:
  Tester(int id, const std::string& name, double salary,
         const std::string& testing_tool, int found_bugs);
  ~Tester() override = default;

  std::string GetType() const override;
  void Work() const override;
  void Print(std::ostream& out) const override;
  void Write(std::ostream& out) const override;
  void Read(std::istream& in) override;
  std::unique_ptr<Employee> Clone() const override;

 private:
  std::string testing_tool_;
  int found_bugs_;
};

class Manager : public Employee {
 public:
  Manager(int id, const std::string& name, double salary,
          const std::string& department, int team_size);
  ~Manager() override = default;

  std::string GetType() const override;
  void Work() const override;
  void Print(std::ostream& out) const override;
  void Write(std::ostream& out) const override;
  void Read(std::istream& in) override;
  std::unique_ptr<Employee> Clone() const override;

 private:
  std::string department_;
  int team_size_;
};

class ServiceStatic {
 public:
  static constexpr std::size_t kCapacity = 10;

  void Add(std::unique_ptr<Employee> employee);
  void RemoveById(int id);
  void PrintAll(std::ostream& out) const;
  void Write(const Employee& employee, const std::string& filename) const;
  void Read(Employee& employee, const std::string& filename) const;
  void SaveAll(const std::string& filename) const;
  void LoadAll(const std::string& filename);
  std::size_t Size() const;
  const Employee& At(std::size_t index) const;

 private:
  std::array<std::unique_ptr<Employee>, kCapacity> employees_;
  std::size_t size_ = 0;

  bool ContainsId(int id) const;
};

class ServiceDynamic {
 public:
  void Add(std::unique_ptr<Employee> employee);
  void RemoveById(int id);
  void PrintAll(std::ostream& out) const;
  void Write(const Employee& employee, const std::string& filename) const;
  void Read(Employee& employee, const std::string& filename) const;
  void SaveAll(const std::string& filename) const;
  void LoadAll(const std::string& filename);
  std::size_t Size() const;
  const Employee& At(std::size_t index) const;

 private:
  std::vector<std::unique_ptr<Employee>> employees_;

  bool ContainsId(int id) const;
};

std::unique_ptr<Employee> CreateEmployee(const std::string& type, int id,
                                         const std::string& name,
                                         double salary,
                                         const std::string& detail,
                                         int metric);
void DemonstratePolymorphism(const Employee& employee);
void DemonstrateExceptions();

#endif
