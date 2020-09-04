//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepository.h"

TaskRepository::TaskRepository(std::unique_ptr<TaskViewInterface> view, std::unique_ptr<TaskStorageInterface> storage)
 : taskView_(std::move(view)), taskStorage_(std::move(storage)){}

const std::unique_ptr<TaskViewInterface>& TaskRepository::GetTaskView() const{
  return taskView_;
}
const std::unique_ptr<TaskStorageInterface>& TaskRepository::GetTaskStorage() const{
  return taskStorage_;
}

AddTaskResult TaskRepository::AddTask(const TaskDTO& task){
  auto taskFromDTO = Task::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate());
  if (!taskFromDTO.has_value()){
    return AddTaskResult(AddTaskResult::ErrorType::TASK_IS_DAMAGED, false);
  }
  auto newTask = taskStorage_->AddTask(taskFromDTO.value());
  if (newTask.has_value()) {
    taskView_->AddTask(newTask.value());
    return AddTaskResult(true);
  }
  return AddTaskResult(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY, false);
}

AddTaskResult TaskRepository::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask){
  auto subtaskFromDTO = Task::Create(subtask.GetName(), subtask.GetLabel(), subtask.GetPriority(), subtask.GetDate());
  if (!subtaskFromDTO.has_value()){
    return AddTaskResult(AddTaskResult::ErrorType::TASK_IS_DAMAGED, false);
  }
  auto newSubtask = taskStorage_->AddSubtask(rootTaskID, subtaskFromDTO.value());
  if (newSubtask.has_value()){
    taskView_->AddTask(newSubtask.value());
    return AddTaskResult(true);
  }
  return AddTaskResult(AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK, false);
}

bool TaskRepository::RemoveTask(const TaskID& id){
  auto task = taskStorage_->GetTask(id);
  if (!task.has_value()){
    return false;
  }
  std::vector<TaskID> idTaskToDelete;
  for (const auto& subtask : task.value()->GetSubtasks()){
    TaskID subtaskID = subtask.second.lock()->GetId();
    idTaskToDelete.push_back(subtaskID);
    // recursive delete subtasks of those subtasks
    RemoveTask(subtaskID);
  }
  // remove subtasks
  for (const auto& id : idTaskToDelete){
    taskStorage_->RemoveTask(id);
    auto task = taskStorage_->GetTask(id);
    if (task.has_value()){
      taskView_->RemoveTask(task.value());
    }
  }
  // remove task
  taskStorage_->RemoveTask(task.value()->GetId());
  taskView_->RemoveTask(task.value());
  auto taskParentID = task.value()->GetParentId();
  if (taskParentID != task.value()->GetId()){
    taskStorage_->GetTask(taskParentID).value()->RemoveTaskFromSubtasks(id);
  }
  return true;
}


bool TaskRepository::PostponeTask(const TaskID& id, const Date& date){
  auto oldTask = taskStorage_->GetTask(id);
  if (!oldTask.has_value()){
    return false;
  }
  taskView_->RemoveTask(oldTask.value());
  auto result = taskStorage_->PostponeTask(id, date);
  taskView_->AddTask(taskStorage_->GetTask(id).value());
  return result;
}