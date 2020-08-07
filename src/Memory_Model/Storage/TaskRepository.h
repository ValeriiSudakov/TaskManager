//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskView.h"
#include "TaskStorage.h"
class TaskRepository {
 public:
  ~TaskRepository();
  TaskRepository();

 public:
  TaskView&     GetTaskView();
  TaskStorage&  GetTaskStorage();

 private:
  TaskView      taskView_;
  TaskStorage   taskStorage_;
 private:
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
