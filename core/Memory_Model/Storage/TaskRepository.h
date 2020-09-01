//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskRepositoryInterface.h"

 class TaskRepository
     : public TaskRepositoryInterface {
 public:
  TaskRepository(std::unique_ptr<TaskViewInterface> view, std::unique_ptr<TaskStorageInterface> storage);

 public:
  const std::unique_ptr<TaskViewInterface>&                 GetTaskView() const override;
  const std::unique_ptr<TaskStorageInterface>&              GetTaskStorage() const override;

  AddTaskResult                                             AddTask(const TaskDTO& task) override;
  AddTaskResult                                             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask) override;
  bool                                                      RemoveTask(const TaskID& id) override;
  bool                                                      PostponeTask(const TaskID& id, const Date& date) override;

 private:
  std::unique_ptr<TaskViewInterface>      taskView_;
  std::unique_ptr<TaskStorageInterface>   taskStorage_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
