//
// Created by R2D2 on 15.07.2020.
//

#include "TaskServiceClass.h"
#include <string>
#include <vector>

TaskServiceClass TaskServiceClass::Create(){
  return TaskServiceClass(std::move(std::make_unique<TaskRepositoryClass>(std::move(std::make_unique<TaskViewClass>()),
                                                                          std::move(std::make_unique<TaskStorageClass>()))));
}

TaskServiceClass::TaskServiceClass(std::unique_ptr<TaskRepository> taskRepository)
  : tasksRepository_(std::move(taskRepository)) {

}

AddTaskResult TaskServiceClass::AddTask(const TaskServiceDTO& task){
  AddTaskResult addNewTask = tasksRepository_->AddTask(MakeTaskRepositoryDTO(task));
  return addNewTask.success_;
}

AddTaskResult TaskServiceClass::AddSubtask(const TaskID& rootTaskID, const TaskServiceDTO& subtask){
  auto dtoSubtask = MakeTaskRepositoryDTO(subtask);
  auto addNewSubtask = tasksRepository_->AddSubtask(rootTaskID, dtoSubtask);
  return addNewSubtask.success_;
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
  return MakeTaskDTO(task.value());
}

std::vector<TaskServiceDTO> TaskServiceClass::GetSubtask(const TaskID& id) const{
  auto subtasks = tasksRepository_->GetSubtask(id);
  return MakeTasksDTO(subtasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasks(bool byPriority) const{
  auto tasks = tasksRepository_->GetTasks();
  return MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTodayTasks(bool byPriority) const{
  auto tasks = tasksRepository_->GetTodayTasks(byPriority);
  return MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetWeekTasks(bool byPriority) const{
  auto tasks = tasksRepository_->GetWeekTasks(byPriority);
  return MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByLabel(const std::string& label, bool byPriority) const{
  auto tasks = tasksRepository_->GetTasksByLabel(label, byPriority);
  return MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByName(const std::string& name, bool byPriority) const{
  auto tasks = tasksRepository_->GetTasksByName(name, byPriority);
  return MakeTasksDTO(tasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByPriority(const Priority& priority) const{
  auto tasks = tasksRepository_->GetTasksByPriority(priority);
  return MakeTasksDTO(tasks);
}

TaskServiceDTO TaskServiceClass::MakeTaskDTO(const TaskRepositoryDTO& task) const {
  auto newTask = TaskServiceDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate(),
                                     task.Complete(), task.GetID());
  assert(newTask.has_value());
  return newTask.value();
}

std::vector<TaskServiceDTO> TaskServiceClass::MakeTasksDTO(const std::vector<TaskRepositoryDTO> &tasksForDTO) const {
  std::vector<TaskServiceDTO> result;
  for (const auto& task : tasksForDTO){
    result.push_back(MakeTaskDTO(task));
  }
  return result;
}

TaskRepositoryDTO TaskServiceClass::MakeTaskRepositoryDTO(const TaskServiceDTO &task) const {
  auto newTask =  TaskRepositoryDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate());
  assert(newTask.has_value());
  return newTask.value();
}

