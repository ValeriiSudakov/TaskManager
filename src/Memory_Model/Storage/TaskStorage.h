//
// Created by valerii.sudakov on 8/4/2020.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_

#include "Memory_Model/Task/TaskEntity.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <map>

class TaskStorage {
 public:
  std::optional<std::shared_ptr<TaskEntity>>       GetTask(const TaskID& taskID) const;
  std::optional<std::shared_ptr<TaskEntity>>       AddTask(const Task& task, const Priority& priority);
  std::optional<std::shared_ptr<TaskEntity>>       AddSubtask(const TaskID& rootTaskID, const Task& subtask,
                                                             const Priority& priority);
  bool                                             RemoveTask(const TaskID& id);
 private:
  TaskIDGenerate                                   taskIDGenerate_;
  std::map<TaskID, std::shared_ptr<TaskEntity>>    tasks_;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_
