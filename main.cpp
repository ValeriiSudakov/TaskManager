#include <iostream>
#include "src/TaskService.h"

int main() {

  TaskService ts;
  Task task = Task::Create("task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  ts.AddTask(task, Task::Priority::HIGH);
  Task subTask = Task::Create("sub task", "label", Task::Priority::HIGH, Date::GetCurrentTime());
  //auto tasks = ts.taskView.GetTasksByName("task", false);
  //ts.AddSubtask(tasks[0].taskID, subTask, Task::Priority::HIGH);
  //ts.taskOutput.Print(ts.taskView.GetTasksByName("sub task", false));
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
