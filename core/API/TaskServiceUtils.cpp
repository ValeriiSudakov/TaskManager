//
// Created by valeriisudakov on 01.10.20.
//

#include "TaskServiceUtils.h"
#include "Memory_Model/Storage/TaskRepositoryClass.h"

std::function<std::unique_ptr<TaskRepository>()> TaskServiceUtils::GetRepositoryFactory(){
  auto factory = [](){
    std::unique_ptr<TaskStorage> storage = std::make_unique<TaskStorageClass>();
    std::unique_ptr<TaskView> view = std::make_unique<TaskViewClass>();
    return std::move(std::make_unique<TaskRepositoryClass>(std::move(view), std::move(storage)));
  };

  return factory;
}

TaskServiceDTO TaskServiceUtils::MakeTaskDTO(const TaskRepositoryDTO& task) {
  auto newTask = TaskServiceDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate(),
                                        task.Complete(), task.GetID());
  assert(newTask.has_value());
  return newTask.value();
}

std::vector<TaskServiceDTO> TaskServiceUtils::MakeTasksDTO(const std::vector<TaskRepositoryDTO> &tasksForDTO) {
  std::vector<TaskServiceDTO> result;
  for (const auto& task : tasksForDTO){
    result.push_back(MakeTaskDTO(task));
  }
  return result;
}

TaskRepositoryDTO TaskServiceUtils::MakeTaskRepositoryDTO(const TaskServiceDTO &task) {
  auto newTask =  TaskRepositoryDTO::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate());
  assert(newTask.has_value());
  return newTask.value();
}