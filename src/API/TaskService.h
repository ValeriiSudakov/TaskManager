//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskID.h"
#include "API/Date/Date.h"
#include "TaskDTO.h"
#include "Memory_Model/Storage/TaskRepository.h"


class TaskService {
 public:
  AddTaskResult             AddTask(const TaskDTO& task);
  AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask);
  bool                      RemoveTask(const TaskID& ID);
  bool                      PostponeTask(const TaskID& ID, const Date& date);

 public:

  std::optional<TaskDTO>    GetTask(const TaskID& id) const;
  std::vector<TaskDTO>      GetTasks(bool byPriority) const;
  std::vector<TaskDTO>      GetTodayTasks(bool byPriority) const;
  std::vector<TaskDTO>      GetWeekTasks(bool byPriority) const;
  std::vector<TaskDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const;
  std::vector<TaskDTO>      GetTasksByName(const std::string& name, bool byPriority) const;
  std::vector<TaskDTO>      GetTasksByPriority(const Priority& priority) const;

 private:
  TaskRepository            tasksRepository_;

 private:
  std::vector<TaskDTO>      MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO) const;
  std::vector<TaskDTO>      MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO) const;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
