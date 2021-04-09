//
// Created by valeriisudakov on 29.10.20.
//

#ifndef TASKMANAGER_CORE_API_UTILS_TASKSERVICECLIENTUTILS_H_
#define TASKMANAGER_CORE_API_UTILS_TASKSERVICECLIENTUTILS_H_
#include "TransportTaskData.pb.h"
#include "TaskServiceDTO.h"
#include "AddTaskResult.h"
#include "AddTaskResult.pb.h"

namespace task_service_client_utils {
  void                                    FillTransportTaskFromDTO(const TaskServiceDTO& source, transport::Task* destination);
  AddTaskResult::ErrorType                FromTransportError(const transport::Error& error);
  std::optional<TaskServiceDTO>           FromTransportTask(const transport::Task& source);

} //task_service_client_utils

#endif //TASKMANAGER_CORE_API_UTILS_TASKSERVICECLIENTUTILS_H_
