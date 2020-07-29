//
// Created by valerii.sudakov on 7/27/2020.
//

#ifndef TASKMANAGER_SRC_TASKVIEW_H_
#define TASKMANAGER_SRC_TASKVIEW_H_
#include "TaskEntity.h"
#include "TaskDTO.h"
#include <map>
#include <vector>

class TaskView {
 public:
  void AddTask(const std::weak_ptr<TaskEntity>& task);
  void RemoveTask(const std::string& taskID);

  std::vector<TaskDTO>  GetTasks(bool SortedByPriority);
  std::vector<TaskDTO>  GetTodayTasks(bool SortedByPriority);
  std::vector<TaskDTO>  GetWeekTasks(bool SortedByPriority);
  std::vector<TaskDTO>  GetTasksByLabel(const std::string& label, bool SortedByPriority);
  std::vector<TaskDTO>  GetTasksByName(const std::string& name, bool SortedByPriority);
  std::vector<TaskDTO>  GetTasksByPriority(Task::Priority taskPriority);

 private:
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>>  byPriority;
  std::map<std::string, std::weak_ptr<TaskEntity>>          byName;
  std::multimap<std::string, std::weak_ptr<TaskEntity>>     byLabel;
  std::multimap<time_t, std::weak_ptr<TaskEntity>>          byDate;
};

#endif //TASKMANAGER_SRC_TASKVIEW_H_
