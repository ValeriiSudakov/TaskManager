//
// Created by valerii.sudakov on 7/27/2020.
//

#ifndef TASKMANAGER_SRC_TASKVIEW_H_
#define TASKMANAGER_SRC_TASKVIEW_H_
#include "TaskEntity.h"
#include <map>
#include <vector>

class TaskView {
 public:
  void AddTask(const std::weak_ptr<TaskEntity>& task);
  void RemoveTask(const std::string& taskID);

  std::vector<Task>  GetTasks(bool SortedByPrioriry);
  std::vector<Task>  GetTodayTasks(bool SortedByPrioriry);
  std::vector<Task>  GetWeekTasks(bool SortedByPrioriry);
  std::vector<Task>  GetTasksByLabel(const std::string& label, bool SortedByPrioriry);
  std::vector<Task>  GetTasksByName(const std::string& name, bool SortedByPrioriry);
 private:
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>>  byPriority;
  std::map<std::string, std::weak_ptr<TaskEntity>>          byName;
  std::multimap<std::string, std::weak_ptr<TaskEntity>>     byLabel;
  std::multimap<time_t, std::weak_ptr<TaskEntity>>          byDate;
};

#endif //TASKMANAGER_SRC_TASKVIEW_H_
