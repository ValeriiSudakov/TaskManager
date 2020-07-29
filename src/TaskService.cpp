//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include "TaskOutput.h"
#include <string>
#include <vector>

TaskService::TaskService() : taskID(){}
TaskService::~TaskService() = default;

void TaskService::AddTask(const Task& task, const Task::Priority& priority){
  TaskID newTaskID = taskID.GenerateID();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks.insert(std::make_pair(newTaskID.GetID(), newEntityTask));
  taskView.AddTask(newEntityTask);
}

bool TaskService::AddSubtask(const TaskID& rootTaskID, const Task& subtask,const Task::Priority& priority){
  if (tasks.find(rootTaskID.GetID()) == tasks.end()){
    return false;
  }
  TaskID newTaskID = taskID.GenerateID();
  auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(newTaskID));
  tasks[rootTaskID.GetID()]->AddSubtasks(newEntityTask);
  tasks.insert(std::make_pair(newTaskID.GetID(), newEntityTask));
  taskView.AddTask(newEntityTask);
  return true;
}


