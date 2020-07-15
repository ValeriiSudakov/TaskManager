//
// Created by R2D2 on 15.07.2020.
//

#include "FullTask.h"
FullTask::FullTask(const std::shared_ptr<TaskEntity> &root_task) : rootTask(root_task) {}
FullTask::~FullTask() = default;
