//
// Created by R2D2 on 29.07.2020.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO() {}

TaskDTO::TaskDTO(const Task& task, const bool& complete, const TaskID& id)
    : task_(task), taskComplete_(complete), taskID_(id) {}