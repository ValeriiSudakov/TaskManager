//
// Created by valeriisudakov on 20.10.20.
//

#ifndef TASKMANAGER_CORE_API_DTO_UTILS_TASKSERVICEDTOUTILS_H_
#define TASKMANAGER_CORE_API_DTO_UTILS_TASKSERVICEDTOUTILS_H_
#include "Repository/Task/Priority.h"
#include <string>

namespace task_service_dto_utils {
  const std::string PriorityToString(const Priority& priority);
};

#endif //TASKMANAGER_CORE_API_DTO_UTILS_TASKSERVICEDTOUTILS_H_
