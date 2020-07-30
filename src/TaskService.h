//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskID.h"
#include "TaskEntity.h"
#include "Date.h"
#include "TaskOutput.h"
#include "TaskView.h"
#include "TaskIDGenerate.h"
#include <map>

class TaskService {
 public:
  TaskOutput  taskOutput;
 public:
  TaskService();
  ~TaskService();

 public:
  void                      AddTask(const Task& task, const Task::Priority& priority);
  bool                      AddSubtask(const TaskID& rootTaskID, const Task& subtask, const Task::Priority& priority);

 public:
  std::vector<TaskDTO>      GetTasks(const bool& byPriority);
  std::vector<TaskDTO>      GetTodayTasks(const bool& byPriority);
  std::vector<TaskDTO>      GetWeekTasks(const bool& byPriority);
  std::vector<TaskDTO>      GetTasksByLabel(const std::string& label,const bool& byPriority);
  std::vector<TaskDTO>      GetTasksByName(const std::string& name, const bool& byPriority);
  std::vector<TaskDTO>      GetTasksByPriority(Task::Priority priority);

 private:
  std::map<unsigned int, std::shared_ptr<TaskEntity>>    tasks;
  TaskIDGenerate                                         taskIDGenerate;
  TaskView                                               taskView;

 private:
  std::vector<TaskDTO>      MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO);
  std::vector<TaskDTO>      MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO);
  TaskDTO                   CreateDTO(const TaskEntity& task);
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
