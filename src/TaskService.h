//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "FullTask.h"
#include "TaskID.h"
#include <map>

class TaskService {
 public:
  TaskService();
  ~TaskService();

 public:
  void AddTask(const Task& task, const Task::Priority& priority);
  void AddSubtask(unsigned int rootTaskID, const Task& subtask,const Task::Priority& priority);

  std::shared_ptr<TaskEntity> GetTaskByName(const std::string& name) const; //for test

  unsigned int GetTaskIDByName(const std::string& name) const;
 private:
  std::vector<std::shared_ptr<FullTask>> tasks;
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>> byPriority;
  TaskID taskID;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
