//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskID.h"
#include "TaskEntity.h"
#include "Date.h"

#include <map>

class TaskService {
 public:
  TaskService();
  ~TaskService();

 public:
  void                        AddTask(const Task& task, const Task::Priority& priority);
  void                        AddSubtask(const std::string& rootTaskID, const Task& subtask,const Task::Priority& priority);

  std::shared_ptr<TaskEntity> GetTaskByName(const std::string& name) const; //for test
  const std::string&          GetTaskIDByName(const std::string& name) const;


  void                        ShowAllTasks(bool SortedByPrioriry);
  void                        ShowAllTodayTasks(bool SortedByPrioriry);
  void                        ShowAllWeekTasks(bool SortedByPrioriry);
  void                        ShowAllTaskByLabel(std::string label, bool SortedByPrioriry);

 private:

  std::map<std::string, std::shared_ptr<TaskEntity>>        tasks;
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>>  byPriority;
  TaskID                                                    taskID;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
