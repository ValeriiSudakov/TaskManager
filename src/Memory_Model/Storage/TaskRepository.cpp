//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepository.h"
TaskRepository::TaskRepository() {}
TaskRepository::~TaskRepository() = default;

TaskView& TaskRepository::GetTaskView() {
  return taskView_;
}
TaskStorage& TaskRepository::GetTaskStorage() {
  return taskStorage_;
}

