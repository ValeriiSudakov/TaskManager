//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskEntity.h"
#include "TaskIDGenerate.h"
#include <map>

class TaskRepository {
 public:
  ~TaskRepository();
  TaskRepository();
  std::weak_ptr<TaskEntity>                   AddTask(const Task& task, const Task::Priority& priority);
  std::optional<std::weak_ptr<TaskEntity>>    AddSubtask(const TaskID& rootTaskID, const Task& subtask,
                                                          const Task::Priority& priority);

 private:
  std::map<unsigned int, std::shared_ptr<TaskEntity>>    tasks_;
  TaskIDGenerate                                         taskIDGenerate_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
