//
// Created by valerii.sudakov on 7/27/2020.
//

#ifndef TASKMANAGER_SRC_TASKVIEW_H_
#define TASKMANAGER_SRC_TASKVIEW_H_
#include "TaskViewInterface.h"

class TaskView : public TaskViewInterface{
 public:
  void                      AddTask(const std::weak_ptr<TaskEntity>& task) override;
  bool                      RemoveTask(const std::weak_ptr<TaskEntity>& task) override;

 public:
  std::vector<TaskEntity>   GetTasks() const override;
  std::vector<TaskEntity>   GetTodayTasks() const override;
  std::vector<TaskEntity>   GetWeekTasks() const override;
  std::vector<TaskEntity>   GetTasksByLabel(const std::string& label) const override;
  std::vector<TaskEntity>   GetTasksByName(const std::string& name) const override;
  std::vector<TaskEntity>   GetTasksByPriority(Priority taskPriority) const override;

 private:
  std::map<Priority, std::map<TaskID, std::weak_ptr<TaskEntity>>>                  byPriority_;
  std::map<std::string, std::map<TaskID, std::weak_ptr<TaskEntity>>>               byName_;
  std::map<std::string, std::map<TaskID, std::weak_ptr<TaskEntity>>>               byLabel_;
  std::map<boost::gregorian::date, std::map<TaskID, std::weak_ptr<TaskEntity>>>    byDate_;

  template <typename CollectionType, typename FindValueType>
  bool RemoveFromMap(CollectionType& collection,const TaskID& id, const FindValueType& findValue);
};

#endif //TASKMANAGER_SRC_TASKVIEW_H_
