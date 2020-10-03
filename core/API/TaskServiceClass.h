//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskService.h"
#include "TaskServiceUtils.h"
#include "Memory_Model/Storage/TaskRepositoryController.h"
/*
 *  Enter point to the program.
 *
 *  All requests to the system starts here.
 *
 *  @author: Valerii Sudakov
 */
class TaskServiceClass : public TaskService {
 public:
  TaskServiceClass(const std::function<std::unique_ptr<TaskRepository>()>& repositoryFactory)
    : repositoryController_(std::move(std::make_unique<TaskRepositoryController>(repositoryFactory))) { }

 public:
  AddTaskResult                    AddTask(const TaskServiceDTO& task) override;
  AddTaskResult                    AddSubtask(const TaskID& rootTaskID, const TaskServiceDTO& subtask) override;
  bool                             RemoveTask(const TaskID& ID) override;
  bool                             PostponeTask(const TaskID& ID, const Date& date) override;
  bool                             Save() override;
  bool                             Load() override;

  bool                             SetTaskComplete(const TaskID& ID) override;

 public:
  std::optional<TaskServiceDTO>    GetTask(const TaskID& id) const override;
  std::vector<TaskServiceDTO>      GetSubtask(const TaskID& id) const override;
  std::vector<TaskServiceDTO>      GetTasks(bool byPriority) const override;
  std::vector<TaskServiceDTO>      GetTodayTasks(bool byPriority) const override;
  std::vector<TaskServiceDTO>      GetWeekTasks(bool byPriority) const override;
  std::vector<TaskServiceDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const override;
  std::vector<TaskServiceDTO>      GetTasksByName(const std::string& name, bool byPriority) const override;

  std::vector<TaskServiceDTO>      GetTasksByPriority(const Priority& priority) const override;

 private:
  std::unique_ptr<TaskRepositoryController> repositoryController_;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
