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
  std::vector<TaskEntity>  GetTasks() const;
  std::vector<TaskEntity>  GetTodayTasks() const;
  std::vector<TaskEntity>  GetWeekTasks() const;
  std::vector<TaskEntity>  GetTasksByLabel(const std::string& label) const;
  std::vector<TaskEntity>  GetTasksByName(const std::string& name) const;
  std::vector<TaskEntity>  GetTasksByPriority(Priority taskPriority) const;

 private:
  std::map<Priority, std::map<unsigned int, std::weak_ptr<TaskEntity>>>                  byPriority_;
  std::map<std::string, std::map<unsigned int, std::weak_ptr<TaskEntity>>>               byName_;
  std::map<std::string, std::map<unsigned int, std::weak_ptr<TaskEntity>>>               byLabel_;
  std::map<boost::gregorian::date, std::map<unsigned int, std::weak_ptr<TaskEntity>>>    byDate_;

};

#endif //TASKMANAGER_SRC_TASKVIEW_H_
