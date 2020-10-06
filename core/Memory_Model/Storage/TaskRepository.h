//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#include "API/AddTaskResult.h"
#include "TaskRepositoryDTO.h"
#include "API/Priority.h"

class TaskRepository{
 public:
  virtual ~TaskRepository() = default;

 public:
  virtual AddTaskResult                       AddTask(const TaskRepositoryDTO& task) = 0;
  virtual AddTaskResult                       AddSubtask(const TaskID& rootTaskID, const TaskRepositoryDTO& subtask) = 0;
  virtual bool                                RemoveTask(const TaskID& id) = 0;
  virtual bool                                PostponeTask(const TaskID& id, const Date& date) = 0;
  virtual bool                                SetTaskComplete(const TaskID& id) = 0;

  virtual std::optional<TaskRepositoryDTO>    GetTask(const TaskID& id) const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetSubtask(const TaskID& id) const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetTasks() const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetTodayTasks(bool byPriority) const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetWeekTasks(bool byPriority) const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetTasksByName(const std::string& name, bool byPriority) const = 0;
  virtual std::vector<TaskRepositoryDTO>      GetTasksByPriority(const Priority& priority) const = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
