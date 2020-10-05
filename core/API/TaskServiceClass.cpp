//
// Created by R2D2 on 15.07.2020.
//

#include "TaskServiceClass.h"
#include <string>
#include <vector>

AddTaskResult TaskServiceClass::AddTask(const TaskServiceDTO& task){
  AddTaskResult addNewTask = repositoryController_->Get()->AddTask(TaskServiceUtils::MakeTaskRepositoryDTO(task));
  return addNewTask;
}

AddTaskResult TaskServiceClass::AddSubtask(const TaskID& rootTaskID, const TaskServiceDTO& subtask){
  auto dtoSubtask = TaskServiceUtils::MakeTaskRepositoryDTO(subtask);
  auto addNewSubtask = repositoryController_->Get()->AddSubtask(rootTaskID, dtoSubtask);
  return addNewSubtask;
}

bool TaskServiceClass::RemoveTask(const TaskID& ID){
  auto result = repositoryController_->Get()->RemoveTask(ID);
  return result;
}

bool TaskServiceClass::Save() {
  return repositoryController_->Save();
}

bool TaskServiceClass::Load() {
  return repositoryController_->Load();
}

bool TaskServiceClass::PostponeTask(const TaskID& ID, const Date& date){
  return repositoryController_->Get()->PostponeTask(ID, date);
}

bool TaskServiceClass::SetTaskComplete(const TaskID &ID) {
  return repositoryController_->Get()->SetTaskComplete(ID);
}

std::optional<TaskServiceDTO> TaskServiceClass::GetTask(const TaskID& id) const{
  auto task = repositoryController_->Get()->GetTask(id);
  if (!task.has_value()){
    return std::nullopt;
  }
  return TaskServiceUtils::MakeTaskDTO(task.value());
}

std::vector<TaskServiceDTO> TaskServiceClass::GetSubtask(const TaskID& id) const{
  auto subtasks = repositoryController_->Get()->GetSubtask(id);
  return TaskServiceUtils::MakeTasksDTO(subtasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasks(bool byPriority) const{
  auto tasks = repositoryController_->Get()->GetTasks();
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTodayTasks(bool byPriority) const{
  auto tasks = repositoryController_->Get()->GetTodayTasks(byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetWeekTasks(bool byPriority) const{
  auto tasks = repositoryController_->Get()->GetWeekTasks(byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByLabel(const std::string& label, bool byPriority) const{
  auto tasks = repositoryController_->Get()->GetTasksByLabel(label, byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByName(const std::string& name, bool byPriority) const{
  auto tasks = repositoryController_->Get()->GetTasksByName(name, byPriority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByPriority(const Priority& priority) const{
  auto tasks = repositoryController_->Get()->GetTasksByPriority(priority);
  return TaskServiceUtils::MakeTasksDTO(tasks);
}


