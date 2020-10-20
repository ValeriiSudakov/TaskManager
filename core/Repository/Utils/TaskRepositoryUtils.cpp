//
// Created by valeriisudakov on 19.10.20.
//

#include "TaskRepositoryUtils.h"

TaskRepositoryDTO task_repository_utils::DTOFromEntity(const TaskEntity &entity) {
  auto task = TaskRepositoryDTO::Create(entity.GetName(), entity.GetLabel(), entity.GetPriority(),
                                        entity.GetDueDate(), entity.IsComplete(), entity.GetId(), entity.GetParentId());
  assert(task.has_value());

  return task.value();
}

std::optional<TaskEntity> task_repository_utils::NewEntityFromDTO(const TaskRepositoryDTO &dto, TaskIDGenerate& generator, std::optional<TaskID> rootID) {
  auto newTask = Task::Create(dto.GetName(), dto.GetLabel(), dto.GetPriority(), dto.GetDate());
  if (!newTask.has_value()){
    return std::nullopt;
  }
  if (rootID.has_value()){
    return TaskEntity(newTask.value(), generator.Generate(), rootID.value());
  } else {
    return TaskEntity(newTask.value(), generator.Generate());
  }
}

void task_repository_utils::SortByPriority(std::vector<TaskRepositoryDTO> &tasks) {
  std::sort(tasks.begin(), tasks.end(),
            [](const TaskRepositoryDTO& first, const TaskRepositoryDTO& second) {
              return first.GetPriority() < second.GetPriority();
            }
  );
}

void task_repository_utils::VectorFromEntitiesToDTO(const std::vector<TaskEntity>& entities,
                                                           std::vector<TaskRepositoryDTO>& dto){
  for (const auto& task : entities){
    dto.push_back(task_repository_utils::DTOFromEntity(task));
  }
}