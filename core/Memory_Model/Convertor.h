//
// Created by valeriisudakov on 17.08.20.
//

#ifndef TASKMANAGER_SRC_CONVERTOR_H_
#define TASKMANAGER_SRC_CONVERTOR_H_
#include "API/TaskServiceDTO.h"
#include "Memory_Model/Task/TaskEntity.h"


namespace convertor{

  namespace toTaskDTO{
  /*
  * Converts from vector of TaskEntities to vector of TaskServiceDTO
  *
  * @param: std::vector of TaskEntity
  *
  * @return-type: std::vector of TaskServiceDTO
  */
  std::vector<TaskServiceDTO> notSortedVector(const std::vector<TaskEntity>& tasksForDTO);

  /*
  * Converts from vector of TaskEntities to vector of TaskServiceDTO and sorts it by priority
  *
  * @param: std::vector of TaskEntity
  *
  * @return-type: std::vector of TaskServiceDTO
  */
  std::vector<TaskServiceDTO> sortedVectorByPriority(const std::vector<TaskEntity>& tasksForDTO);

  }
}
 //convertor
#endif //TASKMANAGER_SRC_CONVERTOR_H_
