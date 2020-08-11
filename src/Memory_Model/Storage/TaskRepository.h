//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskView.h"
#include "TaskStorage.h"
#include "Memory_Model/Task/AddTaskResult.h"
#include "API/TaskDTO.h"
#include "API/Priority.h"

class TaskRepository {
 public:
  ~TaskRepository();
  TaskRepository();

 public:
  TaskView&                 GetTaskView();
  TaskStorage&              GetTaskStorage();

  AddTaskResult             AddTask(const TaskDTO& task, const Priority& priority);
  AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask, const Priority& priority);
  bool                      RemoveTask(const TaskID& id);

 private:
  TaskView      taskView_;
  TaskStorage   taskStorage_;
 private:
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
