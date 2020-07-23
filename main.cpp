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
  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, date);
  ts.AddSubtask(ts.GetTaskIDByName("task"), subTask, Task::Priority::HIGH);
  Task task3 = Task::Create("task3", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task2, Task::Priority::LOW);
  Task task4 = Task::Create("task4", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task2, Task::Priority::LOW);
  Task task5 = Task::Create("task5", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task2, Task::Priority::LOW);
  Task task6 = Task::Create("task6", "label1", Task::Priority::LOW, Date::GetCurrentTime());
  ts.AddTask(task2, Task::Priority::LOW);
  Task subTask1 = Task::Create("sub task1", "label", Task::Priority::HIGH, date);
  ts.AddSubtask(ts.GetTaskIDByName("sub task"), subTask, Task::Priority::HIGH);
  Task subTask2 = Task::Create("sub task2", "label", Task::Priority::HIGH, date);
  ts.AddSubtask(ts.GetTaskIDByName("task"), subTask, Task::Priority::HIGH);
  Task subTask3 = Task::Create("sub task3", "label", Task::Priority::HIGH, date);
  ts.AddSubtask(ts.GetTaskIDByName("sub task"), subTask, Task::Priority::HIGH);


  ts.ShowAllTasks(false);
  std::cout<<"______________________\n";
  try {
    ts.RemoveTask(ts.GetTaskIDByName("sub task"));
    ts.RemoveTask(ts.GetTaskIDByName("task"));
  } catch (std::runtime_error){

  }
  ts.ShowAllTasks(false);
  return 0;
}
