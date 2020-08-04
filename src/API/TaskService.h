//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "Memory Model/TaskID.h"
#include "Memory Model/Date.h"
#include "TaskDTO.h"
#include "Memory Model/TaskRepository.h"

class TaskService {
 public:
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
  std::vector<TaskDTO>      GetTasksByPriority(const Task::Priority& priority);

 private:
  TaskRepository            tasksRepository_;

 private:
  std::vector<TaskDTO>      MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO);
  std::vector<TaskDTO>      MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO);
  TaskDTO                   CreateDTO(const TaskEntity& task);
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
