//
// Created by valeriisudakov on 06/08/2020.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_ADDTASKRESULT_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_ADDTASKRESULT_H_
#include <optional>

struct AddTaskResult {
  enum class ErrorType{
    NOT_ENOUGH_FREE_MEMORY,
    NOT_FOUND_PARENT_TASK
  };
 std::optional<ErrorType> error_;
 bool success_;

  AddTaskResult(bool success) : success_(success) {}
  AddTaskResult(const std::optional<ErrorType> &error, bool success) : error_(error), success_(success) {}
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_ADDTASKRESULT_H_
