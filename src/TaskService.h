//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskID.h"
#include "TaskEntity.h"
#include "Date.h"
#include "TaskOutput.h"

#include <map>

class TaskService {
 public:
  TaskOutput taskOutput;

 public:
  TaskService();
  ~TaskService();

 public:
  void                        AddTask(const Task& task, const Task::Priority& priority);
  void                        AddSubtask(const std::string& rootTaskID, const Task& subtask,const Task::Priority& priority);
  void                        SetTaskComplete(const std::string& taskID);
  void                        RemoveTask(const std::string& taskID);
  void                        PostponeDate(const std::string& taskID, const tm& postponeDate);

  std::shared_ptr<TaskEntity> GetTaskByName(const std::string& name) const; //for test
  const std::string&          GetTaskIDByName(const std::string& name) const;

  std::vector<Task>            GetAllTasks(bool SortedByPrioriry);
  std::vector<Task>            GetAllTodayTasks(bool SortedByPrioriry);
  std::vector<Task>            GetAllWeekTasks(bool SortedByPrioriry);
  std::vector<Task>            GetAllTaskByLabel(std::string label, bool SortedByPrioriry);

 private:
  void                        RemoveTaskFromTasks(const std::string& taskID);
  void                        RemoveTaskFromByPriority(const std::string& taskID);

 private:
  std::map<std::string, std::shared_ptr<TaskEntity>>        tasks;
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>>  byPriority;
  TaskID                                                    taskID;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
