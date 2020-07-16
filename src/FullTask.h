//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_FULLTASK_H_
#define TASKMANAGER_SRC_FULLTASK_H_
#include "TaskEntity.h"
#include <vector>

class FullTask {
 public:
  ~FullTask();
  FullTask(const std::shared_ptr<TaskEntity> &root_task);

 public:
  std::string GetName() const;
  unsigned int GetID() const;

  void AddSubtask(std::shared_ptr<TaskEntity>& root_task);

  void PrintTaskInfo() const;

  TaskEntity& FindSubtask(unsigned int rootTaskID);

  std::vector<std::shared_ptr<FullTask>> &GetSubtasks();

 private:
  std::shared_ptr<TaskEntity> rootTask;
  std::vector<std::shared_ptr<FullTask>> subtasks;
};

#endif //TASKMANAGER_SRC_FULLTASK_H_
