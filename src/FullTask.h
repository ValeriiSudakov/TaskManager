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

  void AddSubtask(std::weak_ptr<FullTask>& fullTask);

  TaskEntity& FindSubtask(unsigned int rootTaskID);

  std::vector<std::weak_ptr<FullTask>> &GetSubtasks();

 private:
  // подумать о том, что тут таски хранятся shared_ptr и в TaskService тоже Shared_ptr
  std::shared_ptr<TaskEntity> rootTask;
  std::vector<std::weak_ptr<FullTask>> subtasks;
};

#endif //TASKMANAGER_SRC_FULLTASK_H_
