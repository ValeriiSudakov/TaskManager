//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "Memory Model/TaskEntity.h"
#include "TaskIDGenerate.h"
#include "TaskView.h"
#include <map>

class TaskRepository {
 public:
  ~TaskRepository();
  TaskRepository();

 public:
  void                                            AddTask(const Task& task, const Task::Priority& priority);
  bool                                            AddSubtask(const TaskID& rootTaskID, const Task& subtask,
                                                          const Task::Priority& priority);

 public:
  std::optional<std::shared_ptr<TaskEntity>>      GetTask(const TaskID& taskID);
  std::vector<TaskEntity>                         GetTasks();
  std::vector<TaskEntity>                         GetTodayTasks();
  std::vector<TaskEntity>                         GetWeekTasks();
  std::vector<TaskEntity>                         GetTasksByLabel(const std::string& label);
  std::vector<TaskEntity>                         GetTasksByName(const std::string& name);
  std::vector<TaskEntity>                         GetTasksByPriority(Task::Priority taskPriority);

 private:
  std::map<unsigned int, std::shared_ptr<TaskEntity>>    tasks_;
  TaskView                                               taskView_;
 private:
  TaskIDGenerate                                         taskIDGenerate_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
