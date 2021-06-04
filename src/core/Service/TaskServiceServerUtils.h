//
// Created by valeriisudakov on 27.10.20.
//

#ifndef TASKMANAGER_CORE_API_UTILS_TASKSERVICESERVERUTILS_H_
#define TASKMANAGER_CORE_API_UTILS_TASKSERVICESERVERUTILS_H_
#include "TaskRepositoryDTO.h"
#include "TransportTaskData.pb.h"
#include "AddTaskResult.pb.h"
#include "AddTaskResult.h"
#include "Response.pb.h"

namespace task_service_server_utils {
  transport::AddTaskResult               ToTransport(const AddTaskResult& result);
  transport::Task                        ToTransport(const TaskRepositoryDTO& task);
  transport::Error                       ToTransport(const AddTaskResult::ErrorType& error);
  void                                   FillTransportTask(const transport::Task& source, transport::Task* destination);
std::optional<TaskRepositoryDTO>         ToTaskRepositoryDTO(const transport::Task& task);
  void                                   SortTasks(std::vector<TaskRepositoryDTO>& tasks);
};

#endif //TASKMANAGER_CORE_API_UTILS_TASKSERVICESERVERUTILS_H_
