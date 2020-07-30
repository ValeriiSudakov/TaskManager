//
// Created by R2D2 on 30.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKCREATERESULT_H_
#define TASKMANAGER_SRC_TASKCREATERESULT_H_
#include <optional>
#include <Task.h>

class TaskCreateResult {
 public:
  enum class Result{
    SUCCESS = 1,
    FAIL
  };

 public:
  TaskCreateResult(Result result, const std::optional<Task> &task, const std::optional<std::string> &message);

 private:
  Result result_;
  std::optional<Task> task_;
  std::optional<std::string> message_;
};

#endif //TASKMANAGER_SRC_TASKCREATERESULT_H_
