#include <iostream>
#include "src/TaskService.h"

int main() {

  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  Task task1 = Task::Create("task1", "label1", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task1, Task::Priority::NONE);
  Task task2 = Task::Create("task2", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task2, Task::Priority::LOW);
  tm date = Date::GetCurrentTime();
  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, date);
  Task task3 = Task::Create("task3", "label2", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task3, Task::Priority::LOW);
  Task task4 = Task::Create("task4", "label2", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task4, Task::Priority::LOW);
  Task task5 = Task::Create("task5", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task5, Task::Priority::LOW);
  Task task6 = Task::Create("task6", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task6, Task::Priority::LOW);
//  //ts.taskOutput.Print(ts.GetAllTasks(false));
//  std::cout<<"______________________\n";
//  try {
//    ts.RemoveTask("sub task");
//    ts.RemoveTask("task");
//  } catch (std::runtime_error){
//
//  }
  return 0;
}
