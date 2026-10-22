#include "stl_lab.h"

#include <algorithm>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

Task::Task(int id, const std::string &title, int priority)
    : id_(id), title_(title), priority_(priority) {}

int Task::GetId() const { return id_; }
const std::string &Task::GetTitle() const { return title_; }
int Task::GetPriority() const { return priority_; }

bool operator<(const Task &left, const Task &right) {
  return left.GetId() < right.GetId();
}

bool operator==(const Task &left, const Task &right) {
  return left.GetId() == right.GetId();
}

namespace {
void PrintTask(const Task &task) {
  std::cout << '#' << task.GetId() << " " << task.GetTitle() << " (P"
            << task.GetPriority() << ')';
}

void DemonstrateIterators() {
  std::cout << "\nКатегорії ітераторів:\n";
  std::istringstream source("7 9 12");
  std::istream_iterator<int> input(source);
  std::cout << "input: " << *input << '\n';
  std::ostream_iterator<int> output(std::cout, " ");
  *output = 7;
  std::cout << "output\n";
  std::forward_list<int> forward_values{1, 2, 3};
  auto forward = forward_values.begin();
  ++forward;
  std::cout << "forward: " << *forward << '\n';
  std::list<int> bidirectional_values{4, 5, 6};
  auto bidirectional = bidirectional_values.end();
  --bidirectional;
  std::cout << "bidirectional: " << *bidirectional << '\n';
  std::vector<int> random_values{10, 20, 30};
  std::cout << "random access: " << random_values.begin()[2] << '\n';
}

void DemonstrateAlgorithms() {
  std::vector<Task> tasks{{3, "Тестування", 2},
                          {1, "Аналіз", 5},
                          {2, "Розробка", 4},
                          {4, "Реліз", 1}};
  std::sort(tasks.begin(), tasks.end());
  auto found = std::find_if(tasks.begin(), tasks.end(), [](const Task &task) {
    return task.GetPriority() >= 4;
  });
  int high_priority =
      std::count_if(tasks.begin(), tasks.end(),
                    [](const Task &task) { return task.GetPriority() >= 4; });
  std::vector<std::string> titles;
  std::transform(tasks.begin(), tasks.end(), std::back_inserter(titles),
                 [](const Task &task) { return task.GetTitle(); });
  std::cout
      << "\nАлгоритми STL: sort, find_if, count_if, transform, remove_if\n";
  std::cout << "find_if: ";
  if (found != tasks.end())
    PrintTask(*found);
  std::cout << "\ncount_if: " << high_priority << "\ntransform: ";
  for (const std::string &title : titles)
    std::cout << title << ' ';
  tasks.erase(
      std::remove_if(tasks.begin(), tasks.end(),
                     [](const Task &task) { return task.GetPriority() == 1; }),
      tasks.end());
  std::cout << "\nПісля remove_if: " << tasks.size() << " задачі\n";
}

void DemonstrateFunctors() {
  int first = 17;
  int second = 5;
  std::cout << "\nФункціональні об'єкти:\n";
  std::cout << "plus=" << std::plus<int>{}(first, second)
            << ", minus=" << std::minus<int>{}(first, second)
            << ", multiplies=" << std::multiplies<int>{}(first, second)
            << ", divides=" << std::divides<int>{}(first, second)
            << ", modulus=" << std::modulus<int>{}(first, second)
            << ", negate=" << std::negate<int>{}(first) << '\n';
  std::cout << "equal_to=" << std::equal_to<int>{}(first, second)
            << ", not_equal_to=" << std::not_equal_to<int>{}(first, second)
            << ", greater=" << std::greater<int>{}(first, second)
            << ", less=" << std::less<int>{}(first, second)
            << ", greater_equal=" << std::greater_equal<int>{}(first, second)
            << ", less_equal=" << std::less_equal<int>{}(first, second) << '\n';
  std::cout << "logical_and=" << std::logical_and<bool>{}(true, false)
            << ", logical_or=" << std::logical_or<bool>{}(true, false)
            << ", logical_not=" << std::logical_not<bool>{}(true) << '\n';
}
}

void DemonstrateStlContainers() {
  Task analysis(1, "Аналіз", 5);
  Task development(2, "Розробка", 4);
  Task testing(3, "Тестування", 3);
  Task release(4, "Реліз", 2);

  std::cout << "Контейнери STL і по три операції:\n";
  std::vector<Task> vector_tasks;
  vector_tasks.push_back(analysis);
  vector_tasks.emplace_back(2, "Розробка", 4);
  vector_tasks.pop_back();
  std::cout << "vector: " << vector_tasks.size() << '\n';

  std::list<Task> list_tasks;
  list_tasks.push_front(analysis);
  list_tasks.push_back(development);
  list_tasks.pop_front();
  std::cout << "list: " << list_tasks.size() << '\n';

  std::deque<Task> deque_tasks;
  deque_tasks.push_front(analysis);
  deque_tasks.push_back(development);
  deque_tasks.pop_back();
  std::cout << "deque: " << deque_tasks.size() << '\n';

  std::set<Task> set_tasks;
  set_tasks.insert(analysis);
  set_tasks.emplace(2, "Розробка", 4);
  set_tasks.erase(analysis);
  std::cout << "set: " << set_tasks.size() << '\n';

  std::multiset<Task> multiset_tasks;
  multiset_tasks.insert(analysis);
  multiset_tasks.emplace(1, "Аналіз", 5);
  std::size_t occurrences = multiset_tasks.count(analysis);
  multiset_tasks.erase(multiset_tasks.find(analysis));
  std::cout << "multiset: було " << occurrences << ", стало "
            << multiset_tasks.size() << '\n';

  std::map<int, Task> map_tasks;
  map_tasks.insert({analysis.GetId(), analysis});
  map_tasks.emplace(development.GetId(), development);
  map_tasks.erase(analysis.GetId());
  std::cout << "map: " << map_tasks.size() << '\n';

  std::multimap<int, Task> multimap_tasks;
  multimap_tasks.insert({analysis.GetPriority(), analysis});
  multimap_tasks.emplace(analysis.GetPriority(), development);
  auto range = multimap_tasks.equal_range(analysis.GetPriority());
  multimap_tasks.erase(range.first, range.second);
  std::cout << "multimap: " << multimap_tasks.size() << '\n';

  std::stack<Task> stack_tasks;
  stack_tasks.push(analysis);
  stack_tasks.emplace(2, "Розробка", 4);
  stack_tasks.pop();
  std::cout << "stack: " << stack_tasks.size() << '\n';

  std::queue<Task> queue_tasks;
  queue_tasks.push(analysis);
  queue_tasks.emplace(2, "Розробка", 4);
  queue_tasks.pop();
  std::cout << "queue: " << queue_tasks.size() << '\n';

  std::priority_queue<Task> priority_tasks;
  priority_tasks.push(analysis);
  priority_tasks.emplace(2, "Розробка", 4);
  priority_tasks.pop();
  std::cout << "priority_queue: " << priority_tasks.size() << '\n';

  PrintTask(testing);
  std::cout << "\n";
  PrintTask(release);
  std::cout << "\n";
  DemonstrateIterators();
  DemonstrateAlgorithms();
  DemonstrateFunctors();
}
