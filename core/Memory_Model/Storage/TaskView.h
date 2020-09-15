//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKVIEWINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKVIEWINTERFACE_H_

#include "Memory_Model/Task/TaskEntity.h"
#include "API/Priority.h"
#include <map>
#include <vector>

class TaskView {
 public:
 virtual ~TaskView() = default;

 public:
  virtual void                      AddTask(const std::weak_ptr<TaskEntity> &task) = 0;
  virtual bool                      RemoveTask(const std::weak_ptr<TaskEntity> &task) = 0;

 public:
  virtual std::vector<TaskEntity>   GetTasks() const = 0;
  virtual std::vector<TaskEntity>   GetTodayTasks() const = 0;
  virtual std::vector<TaskEntity>   GetWeekTasks() const = 0;
  virtual std::vector<TaskEntity>   GetTasksByLabel(const std::string &label) const = 0;
  virtual std::vector<TaskEntity>   GetTasksByName(const std::string &name) const = 0;
  virtual std::vector<TaskEntity>   GetTasksByPriority(Priority taskPriority) const = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKVIEWINTERFACE_H_
