#include <iostream>
#include "TaskService.h"
int main() {

  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  Task task1 = Task::Create("task1", "label1", Task::Priority::NONE, Date::GetCurrentTime());
  ts.AddTask(task1, Task::Priority::NONE);
  Task task2 = Task::Create("task2", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task2, Task::Priority::LOW);
  tm date = Date::GetCurrentTime();
  //Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, date);
  //ts.AddSubtask(ts.GetTaskIDByName("task"), subTask, Task::Priority::HIGH);
  //ts.ShowAllTasks(false);
  std::cout<<"______________________\n";
  try {
    ts.RemoveTask(ts.GetTaskIDByName("task3213"));
  } catch (std::runtime_error){

  }
  ts.ShowAllTasks(false);
  return 0;
}
