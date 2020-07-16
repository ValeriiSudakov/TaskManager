//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"

TaskService::TaskService() : tasksID(0){}
TaskService::~TaskService() = default;

std::shared_ptr<TaskEntity> TaskService::GetTaskByName(const std::string name) const {
    std::shared_ptr<TaskEntity> sp;
    for (auto taskInfo : byPriority){
      sp = taskInfo.second.lock();
      if (sp->GetTaskName() == name){
        return sp;
      }
      sp.reset();
    }
}

void TaskService::AddTask(const Task& task, const Task::Priority priority){
  // weak pointer to root task (to multimap)
  auto taskShared = std::make_shared<Task>(task);
  auto newTask = std::make_shared<TaskEntity>(taskShared, tasksID++);
  tasks.push_back(std::make_shared<FullTask>(newTask));

  std::weak_ptr<TaskEntity> newTaskPtr(newTask);
  byPriority.insert(std::make_pair(priority, newTaskPtr));
}

void TaskService::AddSubtask(unsigned int rootTaskID, const  Task& subtask, Task::Priority priority){
  for (auto task : tasks) {
    if (task->GetID() == rootTaskID) {
      AddTask(subtask, priority);
      return;
    } else if (!task->GetSubtasks().empty()) {
      for (auto subtask : task->GetSubtasks()) {
        Task &rootTask = *(subtask->FindSubtask(rootTaskID).GetTask());
      }
    }
  }
}

unsigned int TaskService::GetTaskIDByName(const std::string name) const{
  for (auto task : tasks) {
    if (task->GetName() == name){
      return task->GetID();
    }
  }
}
