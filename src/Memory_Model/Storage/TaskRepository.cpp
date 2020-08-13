//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepository.h"

const TaskView& TaskRepository::GetTaskView() const{
  return taskView_;
}
const TaskStorage& TaskRepository::GetTaskStorage() const{
  return taskStorage_;
}

AddTaskResult TaskRepository::AddTask(const TaskDTO& task, const Priority& priority){
  auto taskFromDTO = Task::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate());
  if (!taskFromDTO.has_value()){
    return AddTaskResult(AddTaskResult::ErrorType::TASK_IS_DAMAGED, false);
  }
  auto newTask = taskStorage_.AddTask(taskFromDTO.value(), priority);
  if (newTask.has_value()) {
    taskView_.AddTask(newTask.value());
    return AddTaskResult(true);
  }
  return AddTaskResult(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY, false);
}

AddTaskResult TaskRepository::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask,const Priority& priority){
  auto subtaskFromDTO = Task::Create(subtask.GetName(), subtask.GetLabel(), subtask.GetPriority(), subtask.GetDate());
  if (!subtaskFromDTO.has_value()){
    return AddTaskResult(AddTaskResult::ErrorType::TASK_IS_DAMAGED, false);
  }
  auto newSubtask = taskStorage_.AddSubtask(rootTaskID, subtaskFromDTO.value(), priority);
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
  for (const auto& subtask : task.value()->GetSubtasks()){
    TaskID subtaskID = subtask.second.lock()->GetId();
    idTaskToDelete.push_back(subtaskID);
    // recursive delete subtasks of those subtasks
    RemoveTask(subtaskID);
  }
  // remove subtasks
  for (const auto& id : idTaskToDelete){
    taskStorage_.RemoveTask(id.Get());
  }
  // remove task
  taskStorage_.RemoveTask(task.value()->GetId());
  auto taskParentID = task.value()->GetParentId();
  if (taskParentID.Get() != task.value()->GetId().Get()){
      taskStorage_.GetTask(taskParentID).value()->RemoveTaskFromSubtasks(id);
  }
  return true;
}