//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#include "API/AddTaskResult.h"
#include "API/TaskDTO.h"
#include "API/Priority.h"
#include "TaskView.h"
#include "TaskStorage.h"

class TaskRepositoryInterface{
 public:
  virtual ~TaskRepositoryInterface() = default;

 public:
  virtual const std::unique_ptr<TaskViewInterface>&         GetTaskView() const = 0;
  virtual const std::unique_ptr<TaskStorageInterface>&      GetTaskStorage() const = 0;

  virtual AddTaskResult                                     AddTask(const TaskDTO& task) = 0;
  virtual AddTaskResult                                     AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask) = 0;
  virtual bool                                              RemoveTask(const TaskID& id) = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
