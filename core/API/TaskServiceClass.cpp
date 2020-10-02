//
// Created by R2D2 on 15.07.2020.
//

#include "TaskServiceClass.h"
#include <string>
#include <vector>

AddTaskResult TaskServiceClass::AddTask(const TaskServiceDTO& task){
  AddTaskResult addNewTask = tasksRepository_->AddTask(TaskServiceUtils::MakeTaskRepositoryDTO(task));
  return addNewTask;
}

AddTaskResult TaskServiceClass::AddSubtask(const TaskID& rootTaskID, const TaskServiceDTO& subtask){
  auto dtoSubtask = TaskServiceUtils::MakeTaskRepositoryDTO(subtask);
  auto addNewSubtask = tasksRepository_->AddSubtask(rootTaskID, dtoSubtask);
  return addNewSubtask;
}

bool TaskServiceClass::RemoveTask(const TaskID& ID){
  auto result = tasksRepository_->RemoveTask(ID);
  return result;
}


bool TaskServiceClass::PostponeTask(const TaskID& ID, const Date& date){
  return tasksRepository_->PostponeTask(ID, date);
}

bool TaskServiceClass::SetTaskComplete(const TaskID &ID) {
  return tasksRepository_->SetTaskComplete(ID);
}

std::optional<TaskServiceDTO> TaskServiceClass::GetTask(const TaskID& id) const{
  auto task = tasksRepository_->GetTask(id);
  if (!task.has_value()){
    return std::nullopt;
  }
  return TaskServiceUtils::MakeTaskDTO(task.value());
}

std::vector<TaskServiceDTO> TaskServiceClass::GetSubtask(const TaskID& id) const{
  auto subtasks = tasksRepository_->GetSubtask(id);
  return TaskServiceUtils::MakeTasksDTO(subtasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasks(bool byPriority) const{
  auto tasks = tasksRepository_->GetTasks();
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTodayTasks(bool byPriority) const{
  auto tasks = tasksRepository_->GetTodayTasks(byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetWeekTasks(bool byPriority) const{
  auto tasks = tasksRepository_->GetWeekTasks(byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByLabel(const std::string& label, bool byPriority) const{
  auto tasks = tasksRepository_->GetTasksByLabel(label, byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByName(const std::string& name, bool byPriority) const{
  auto tasks = tasksRepository_->GetTasksByName(name, byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByPriority(const Priority& priority) const{
  auto tasks = tasksRepository_->GetTasksByPriority(priority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}


