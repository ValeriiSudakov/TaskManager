//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKSTORAGEINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKSTORAGEINTERFACE_H_
#include "Memory_Model/Task/TaskEntity.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <map>
class TaskStorage{
 public:
  virtual ~TaskStorage() = default;

 public:
  virtual std::optional<std::shared_ptr<TaskEntity>>       GetTask(const TaskID& taskID) const = 0;
  virtual std::optional<std::shared_ptr<TaskEntity>>       AddTask(const Task& task) = 0;
  virtual std::optional<std::shared_ptr<TaskEntity>>       AddSubtask(const TaskID& rootTaskID, const Task& subtask) = 0;

  virtual bool                                             RemoveTask(const TaskID& id) = 0;
  virtual bool                                             PostponeTask(const TaskID& id, const Date& date) = 0;

  virtual bool                                             SaveToFile(const std::string& fileName) = 0;
  virtual bool                                             LoadFromFile(const std::string& fileName) = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKSTORAGEINTERFACE_H_
