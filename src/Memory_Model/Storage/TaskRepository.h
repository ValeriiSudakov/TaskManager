//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskRepositoryInterface.h"

 class TaskRepository
     : public TaskRepositoryInterface {

 public:
  const TaskView&                 GetTaskView() const override;
  const TaskStorage&              GetTaskStorage() const override;

  AddTaskResult                   AddTask(const TaskDTO& task, const Priority& priority) override;
  AddTaskResult                   AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask, const Priority& priority) override;
  bool                            RemoveTask(const TaskID& id) override;

 private:
  TaskView      taskView_;
  TaskStorage   taskStorage_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
