//
// Created by valeriisudakov on 17.08.20.
//

#ifndef TASKMANAGER_SRC_CONVERTOR_H_
#define TASKMANAGER_SRC_CONVERTOR_H_
#include "API/TaskDTO.h"
#include "Memory_Model/Task/TaskEntity.h"


namespace convertor{

  namespace toTaskDTO{
  /*
  * Converts from vector of TaskEntities to vector of TaskDTO
  *
  * @param: std::vector of TaskEntity
  *
  * @return-type: std::vector of TaskDTO
  */
  std::vector<TaskDTO> notSortedVector(const std::vector<TaskEntity>& tasksForDTO);

  /*
  * Converts from vector of TaskEntities to vector of TaskDTO and sorts it by priority
  *
  * @param: std::vector of TaskEntity
  *
  * @return-type: std::vector of TaskDTO
  */
  std::vector<TaskDTO> sortedVectorByPriority(const std::vector<TaskEntity>& tasksForDTO);

  }
}
 //convertor
#endif //TASKMANAGER_SRC_CONVERTOR_H_
