#ifndef STL_LAB_H_
#define STL_LAB_H_

#include <string>

class Task {
public:
  Task(int id, const std::string &title, int priority);

  int GetId() const;
  const std::string &GetTitle() const;
  int GetPriority() const;

private:
  int id_;
  std::string title_;
  int priority_;
};

bool operator<(const Task &left, const Task &right);
bool operator==(const Task &left, const Task &right);

void DemonstrateStlContainers();

#endif
