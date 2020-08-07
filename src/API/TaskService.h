//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "Memory_Model/Task/TaskID.h"
#include "Memory_Model/Date/Date.h"
#include "TaskDTO.h"
#include "Memory_Model/Storage/TaskRepository.h"
#include "Memory_Model/Task/AddTaskResult.h"
class TaskService {
 public:
  AddTaskResult             AddTask(const TaskDTO& task, const Task::Priority& priority);
  AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask, const Task::Priority& priority);

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
