//
// Created by valeriisudakov on 06/08/2020.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_ADDTASKRESULT_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_ADDTASKRESULT_H_
#include <optional>
#include "Repository/Task/ID/TaskID.h"

/*
 * Contains information about result of the add operation
 *
 * @author: Valerii Sudakov
 */
struct AddTaskResult {
  enum class ErrorType{
    NOT_ENOUGH_FREE_MEMORY,
    NOT_FOUND_PARENT_TASK,
    TASK_IS_DAMAGED,
    BAD_CONNECTION
  };
  std::optional<ErrorType>   error_;
  std::optional<TaskID>      id_;
  bool                       success_;

  static AddTaskResult       Success(const TaskID& id) {
    return AddTaskResult(std::nullopt, true, id);
  }
  static AddTaskResult       Failed(const AddTaskResult::ErrorType& error) {
    return AddTaskResult(error, false, std::nullopt);
  }

 private:
  AddTaskResult(const std::optional<ErrorType>& error, bool success, const std::optional<TaskID>& id)
    : error_(error), success_(success), id_(id) {}
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_ADDTASKRESULT_H_
