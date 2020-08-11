//
// Created by valerii.sudakov on 7/27/2020.
//

#ifndef TASKMANAGER_SRC_TASKVIEW_H_
#define TASKMANAGER_SRC_TASKVIEW_H_
#include "Memory_Model/Task/TaskEntity.h"
#include "API/Priority.h"
#include <map>
#include <vector>

class TaskView {
 public:
  void AddTask(const std::weak_ptr<TaskEntity>& task);

 public:
  std::vector<TaskEntity>  GetTasks();
  std::vector<TaskEntity>  GetTodayTasks();
  std::vector<TaskEntity>  GetWeekTasks();
  std::vector<TaskEntity>  GetTasksByLabel(const std::string& label);
  std::vector<TaskEntity>  GetTasksByName(const std::string& name);
  std::vector<TaskEntity>  GetTasksByPriority(Priority taskPriority);

 private:
  std::map<Priority, std::map<unsigned int, std::weak_ptr<TaskEntity>>>                  byPriority_;
  std::map<std::string, std::map<unsigned int, std::weak_ptr<TaskEntity>>>               byName_;
  std::map<std::string, std::map<unsigned int, std::weak_ptr<TaskEntity>>>               byLabel_;
  std::map<boost::gregorian::date, std::map<unsigned int, std::weak_ptr<TaskEntity>>>    byDate_;

};

#endif //TASKMANAGER_SRC_TASKVIEW_H_
