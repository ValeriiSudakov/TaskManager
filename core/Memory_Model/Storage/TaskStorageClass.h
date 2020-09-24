//
// Created by valerii.sudakov on 8/4/2020.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_

#include "TaskStorage.h"

class TaskStorageClass : public TaskStorage{
 public:
  TaskStorageClass();

 public:
  std::map<TaskID, std::shared_ptr<TaskEntity>>    GetTasks() const override;
  std::optional<std::shared_ptr<TaskEntity>>       GetTask(const TaskID& taskID) const override;
  std::optional<std::shared_ptr<TaskEntity>>       AddTask(const Task& task) override;
  std::optional<std::shared_ptr<TaskEntity>>       AddSubtask(const TaskID& rootTaskID, const Task& subtask) override;
  bool                                             RemoveTask(const TaskID& id) override;
  bool                                             PostponeTask(const TaskID& id, const Date& date) override;
 private:
  TaskIDGenerate                                   taskIDGenerate_;
  std::map<TaskID, std::shared_ptr<TaskEntity>>    tasks_;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_TASKSTORAGE_H_
