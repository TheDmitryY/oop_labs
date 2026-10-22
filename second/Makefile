CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = main
SRCS = main.cpp department.cpp project.cpp project_module.cpp task_assignment.cpp worker.cpp personnel_system.cpp stl_lab.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
