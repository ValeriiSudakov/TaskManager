//
// Created by R2D2 on 15.07.2020.
//

#include "TaskEntity.h"
#include <exception>

TaskEntity::TaskEntity(const Task& task, TaskID ID)
    : task_(task), id_(ID), parentID_(ID), complete_(false) {}


TaskEntity::TaskEntity(const Task &task, TaskID ID, TaskID parentID)
: task_(task), id_(ID), parentID_(parentID), complete_(false)  { }

TaskEntity::~TaskEntity() = default;


const TaskID TaskEntity::GetId() const {
  return id_;
}

const TaskID TaskEntity::GetParentId() const {
    return parentID_;
}

bool TaskEntity::IsComplete() const {
  if (subtasks_.empty()){
    return complete_;
  }
  for (auto subtask : subtasks_){
   if (!subtask.second.lock()->IsComplete()){
     return false;
   }
  }
  return true;
}

void TaskEntity::SetComplete() {
  complete_ = true;
  for (auto subtask : subtasks_){
    if (subtask.second.lock() != nullptr){
      subtask.second.lock()->SetComplete();
    }
  }
}


bool TaskEntity::PostponeDate(const Date& newDate){
    if (newDate.Get().day_number() < Date::GetCurrentTime().day_number()){
        return false;
    }

    auto newTask = Task::Create(task_.GetName(), task_.GetLabel(), task_.GetPriority(), newDate);
    if (newTask.has_value()){
        task_ = newTask.value();
        return true;
    }
    return false;
}

const std::string TaskEntity::GetTaskLabel() const{
  return task_.GetLabel();
}


const Priority TaskEntity::GetTaskPriority() const {
  return task_.GetPriority();
}

const Date TaskEntity::GetTaskDueDate() const{
  return task_.GetDueDate();
}

const std::string TaskEntity::GetTaskName() const{
  return task_.GetName();
}

const Task TaskEntity::GetTask() const {
  return task_;
}

bool TaskEntity::RemoveTaskFromSubtasks(const TaskID& id){
  auto subtask = subtasks_.find(id);
  if (subtask != subtasks_.end()){
      subtasks_.erase(subtask);
      return true;
  }
  return false;
}

void TaskEntity::AddSubtasks(std::weak_ptr<TaskEntity> subtask) {
    subtasks_.insert(std::make_pair(subtask.lock()->GetId(), subtask));
    complete_ = false;
}

const std::map<TaskID, std::weak_ptr<TaskEntity>> TaskEntity::GetSubtasks() const {
  return subtasks_;
}
