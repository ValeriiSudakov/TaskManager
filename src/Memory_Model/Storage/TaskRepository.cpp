//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepository.h"
TaskRepository::TaskRepository() {}
TaskRepository::~TaskRepository() = default;

TaskView& TaskRepository::GetTaskView() {
  return taskView_;
}
TaskStorage& TaskRepository::GetTaskStorage() {
  return taskStorage_;
}

AddTaskResult TaskRepository::AddTask(const TaskDTO& task, const Task::Priority& priority){
  auto newTask = taskStorage_.AddTask(task.GetTask(), priority);
  if (newTask.has_value()) {
    taskView_.AddTask(newTask.value());
    return AddTaskResult(true);
  }
  return AddTaskResult(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY, false);
}

AddTaskResult TaskRepository::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask,const Task::Priority& priority){
  auto newSubtask = taskStorage_.AddSubtask(rootTaskID, subtask.GetTask(), priority);
  if (newSubtask.has_value()){
    taskView_.AddTask(newSubtask.value());
    return AddTaskResult(true);
  }
  return AddTaskResult(AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK, false);
}

bool TaskRepository::RemoveTask(const TaskID& id){
  auto task = taskStorage_.GetTask(id);
  if (!task.has_value()){
    return false;
  }
  std::vector<TaskID> idTaskToDelete;
  for (auto subtask : task.value()->GetSubtasks()){
    TaskID subtaskID = subtask.lock()->GetId();
    idTaskToDelete.push_back(subtaskID);
    // recursive delete subtasks of those subtasks
    RemoveTask(subtaskID);
  }
  // remove subtasks
  for (auto id : idTaskToDelete){
    taskStorage_.RemoveTask(id.GetID());
  }
  // remove task
  taskStorage_.RemoveTask(task.value()->GetId());
  return true;
}