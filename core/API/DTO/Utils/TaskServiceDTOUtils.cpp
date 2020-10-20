//
// Created by valeriisudakov on 20.10.20.
//

#include "TaskServiceDTOUtils.h"

const std::string task_service_dto_utils::PriorityToString(const Priority &priority) {
  if (priority == Priority::FIRST){
    return "first";
  } else if (priority == Priority::SECOND){
    return "second";
  } else if (priority == Priority::THIRD){
    return "third";
  } else {
    return "none";
  }
}