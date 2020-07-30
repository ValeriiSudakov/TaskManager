//
// Created by R2D2 on 30.07.2020.
//

#include "TaskCreateResult.h"
TaskCreateResult::TaskCreateResult(TaskCreateResult::Result result,
                                   const std::optional<Task> &task,
                                   const std::optional<std::string> &message)
    : result_(result), task_(task), message_(message) {}
