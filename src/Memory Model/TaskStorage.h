//
// Created by valerii.sudakov on 8/4/2020.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_

#include "Memory Model/TaskEntity.h"
#include "TaskIDGenerate.h"
#include <map>

class TaskStorage {
 public:
  std::optional<std::shared_ptr<TaskEntity>>             GetTask(const TaskID& taskID);
  std::shared_ptr<TaskEntity>                            AddTask(const Task& task, const Task::Priority& priority);
  std::optional<std::shared_ptr<TaskEntity>>             AddSubtask(const TaskID& rootTaskID, const Task& subtask,
                                                             const Task::Priority& priority);
 private:
  TaskIDGenerate                                         taskIDGenerate_;
  std::map<unsigned int, std::shared_ptr<TaskEntity>>    tasks_;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_
