//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include "TaskOutput.h"

TaskService::TaskService() : taskID(){}
TaskService::~TaskService() = default;

std::shared_ptr<TaskEntity> TaskService::GetTaskByName(const std::string& name) const {
    std::shared_ptr<TaskEntity> sp;
    for (const auto& taskInfo : byPriority){
      sp = taskInfo.second.lock();
      if (sp->GetTaskName() == name){
        return sp;
      }
      sp.reset();
    }
}

void TaskService::AddTask(const Task& task, const Task::Priority& priority){
  // weak pointer to root task (to multimap)
  auto taskShared = std::make_shared<Task>(task);
  auto newTask = std::make_shared<TaskEntity>(taskShared, taskID.CreateID());
  tasks.push_back(std::make_shared<FullTask>(newTask));

  std::weak_ptr<TaskEntity> newTaskPtr(newTask);
  byPriority.insert(std::make_pair(priority, newTaskPtr));
}

void TaskService::AddSubtask(unsigned int rootTaskID, const Task& subtask,const Task::Priority& priority){
  for (auto task : tasks) {
    if (task->GetID() == rootTaskID) {
      AddTask(subtask, priority);
      return;
    } else if (!task->GetSubtasks().empty()) {
      std::shared_ptr<FullTask> subtaskPtr;
      for (auto subtask : task->GetSubtasks()) {
        subtaskPtr = subtask.lock();
        Task &roooTask = *subtaskPtr->FindSubtask(rootTaskID).GetTask();
        subtaskPtr.reset();
      }
    }
  }
}

unsigned int TaskService::GetTaskIDByName(const std::string& name) const{
  for (auto task : tasks) {
    if (task->GetName() == name){
      return task->GetID();
    }
  }
}


void TaskService::ShowAllTasks(bool SortedByPrioriry){
  TaskOutput to;
  if (SortedByPrioriry){
    std::shared_ptr<TaskEntity> taskPtr;
    for (auto task : byPriority){
      taskPtr = task.second.lock();
      to.Print(*taskPtr->GetTask());
      taskPtr.reset();
    }
  } else {
    for (auto task : tasks){
      to.Print(*task->GetRootTask()->GetTask());
    }
  }

}
void TaskService::ShowAllTodayTasks(bool SortedByPrioriry){
  tm currentTime = Date::GetCurrentTime();
  TaskOutput to;

  if (SortedByPrioriry){
    std::shared_ptr<TaskEntity> taskPtr;

    for (auto task : byPriority){
      taskPtr = task.second.lock();

      if (currentTime.tm_mon == taskPtr->GetTask()->GetDueDate().tm_mon &&
          currentTime.tm_mday == taskPtr->GetTask()->GetDueDate().tm_mday){
        to.Print(*taskPtr->GetTask());
      }
      taskPtr.reset();
    }
  } else {
    for (auto task : tasks){
      if (currentTime.tm_mon == task->GetRootTask()->GetTaskDueDate().tm_mon &&
          currentTime.tm_mday == task->GetRootTask()->GetTaskDueDate().tm_mday){
        to.Print(*task->GetRootTask()->GetTask());
      }
    }
 }
}

void TaskService::ShowAllWeekTasks(bool SortedByPrioriry){

}

void TaskService::ShowAllTaskByLabel(std::string label, bool SortedByPrioriry){
  TaskOutput to;
  if (SortedByPrioriry){
    std::shared_ptr<TaskEntity> taskPtr;
    for (auto task : byPriority){
      taskPtr = task.second.lock();
      if (taskPtr->GetTaskLabel() == label) {
        to.Print(*taskPtr->GetTask());
      }
      taskPtr.reset();
    }
  } else {
    for (auto task : tasks){
      if (task->GetRootTask()->GetTaskLabel() == label) {
        to.Print(*task->GetRootTask()->GetTask());
      }
    }
  }
}