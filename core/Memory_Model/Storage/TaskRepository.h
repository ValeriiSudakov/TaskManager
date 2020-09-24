//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#include "API/AddTaskResult.h"
#include "API/TaskDTO.h"
#include "API/Priority.h"
#include "TaskViewClass.h"
#include "TaskStorageClass.h"

class TaskRepository{
 public:
  virtual ~TaskRepository() = default;

 public:
  virtual void                                              ResetRepository() = 0;
  virtual const std::unique_ptr<TaskView>&                  GetTaskView() const = 0;
  virtual const std::unique_ptr<TaskStorage>&               GetTaskStorage() const = 0;

  virtual AddTaskResult                                     AddTask(const Task& task) = 0;
  virtual AddTaskResult                                     AddSubtask(const TaskID& rootTaskID, const Task& subtask) = 0;
  virtual bool                                              RemoveTask(const TaskID& id) = 0;
  virtual bool                                              PostponeTask(const TaskID& id, const Date& date) = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
