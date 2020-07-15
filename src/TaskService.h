//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "FullTask.h"
#include <map>

class TaskService {
 public:

 private:
  std::vector<std::shared_ptr<FullTask>> tasks;
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>> byPriority;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
