//
// Created by valeriisudakov on 01.10.20.
//

#ifndef TASKMANAGER_CORE_API_TASKSERVICEUTILS_H_
#define TASKMANAGER_CORE_API_TASKSERVICEUTILS_H_
#include "TaskServiceDTO.h"
#include "Memory_Model/Storage/TaskRepositoryDTO.h"

class TaskRepository;

namespace TaskServiceUtils {

/*
 * Converts from vector of TaskRepositoryDTO to vector of TaskServiceDTO
 *
 * @param: std::vector of TaskRepositoryDTO
 *
 * @return-type: std::vector of TaskServiceDTO
 */
std::vector<TaskServiceDTO>         MakeTasksDTO(const std::vector<TaskRepositoryDTO>& tasksForDTO);

/*
 * Converts from TaskRepositoryDTO to vector of TaskServiceDTO
 *
 * @param: TaskRepositoryDTO
 *
 * @return-type: std::vector of TaskServiceDTO
 */
std::optional<TaskServiceDTO>       MakeTaskDTO(const TaskRepositoryDTO& task);

/*
 * Converts from TaskServiceDTO to vector of TaskRepositoryDTO
 *
 * @param: TaskServiceDTO
 *
 * @return-type: TaskRepositoryDTO
 */
TaskRepositoryDTO                   MakeTaskRepositoryDTO(const TaskServiceDTO& task);
};

#endif //TASKMANAGER_CORE_API_TASKSERVICEUTILS_H_
