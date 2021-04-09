//
// Created by valeriisudakov on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskRepository.h"
#include "TaskViewClass.h"
#include "TaskStorageClass.h"
#include "TaskIDGenerate.h"
/*
 * TaskRepository class.
 * Class-holder of TaskStorage, TaskView and TaskIDGenerator.
 * Performs all repository edit-operation: Create, Remove, Postpone, Complete
 * and makes requests to Repository and View to.
 *
 * Get tasks requests: makes requests to view or storage, get tasks from there,
 * convert to TaskRepositoryDTO and return it.
 *
 * @see: TaskRepository.h
 *
 * @author: Valerii Sudakov.
 */
 class TaskRepositoryClass
     : public TaskRepository {
 public:
  TaskRepositoryClass(std::unique_ptr<TaskView> view, std::unique_ptr<TaskStorage> storage);

 public:
  AddTaskResult                       AddTask(const TaskRepositoryDTO& task) override;
  AddTaskResult                       AddSubtask(const TaskID& rootTaskID, const TaskRepositoryDTO& subtask) override;
  bool                                RemoveTask(const TaskID& id) override;
  bool                                PostponeTask(const TaskID& id, const Date& date) override;
  bool                                SetTaskComplete(const TaskID& id) override;

  std::optional<TaskRepositoryDTO>    GetTask(const TaskID& id) const override;
  std::vector<TaskRepositoryDTO>      GetSubtask(const TaskID& id) const override;
  std::vector<TaskRepositoryDTO>      GetTasks() const override;
  std::vector<TaskRepositoryDTO>      GetTodayTasks(bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetWeekTasks(bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTasksByName(const std::string& name, bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTasksByPriority(const Priority& priority) const override;

 private:
  std::unique_ptr<TaskView>           taskView_;
  std::unique_ptr<TaskStorage>        taskStorage_;
  TaskIDGenerate                      taskIDGenerate_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
