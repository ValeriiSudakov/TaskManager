//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskService.h"
#include "Memory_Model/Storage/TaskRepository.h"
#include "Memory_Model/Convertor.h"

/*
 *  Enter point to the program.
 *
 *  All requests to the system starts here.
 *
 *  @author: Valerii Sudakov
 */
class TaskServiceClass : public TaskService {
 public:
  static TaskServiceClass Create();
 public:

  AddTaskResult             AddTask(const TaskDTO& task) override;
  AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask) override;
  bool                      RemoveTask(const TaskID& ID) override;
  bool                      PostponeTask(const TaskID& ID, const Date& date) override;
  bool                      SetTaskComplete(const TaskID& ID) override;

 public:

  std::optional<TaskDTO>    GetTask(const TaskID& id) const override;
  std::vector<TaskDTO>      GetSubtask(const TaskID& id) const override;
  std::vector<TaskDTO>      GetTasks(bool byPriority) const override;
  std::vector<TaskDTO>      GetTodayTasks(bool byPriority) const override;
  std::vector<TaskDTO>      GetWeekTasks(bool byPriority) const override;
  std::vector<TaskDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const override;
  std::vector<TaskDTO>      GetTasksByName(const std::string& name, bool byPriority) const override;
  std::vector<TaskDTO>      GetTasksByPriority(const Priority& priority) const override;

 private:

  std::unique_ptr<TaskRepositoryInterface>            tasksRepository_;

  TaskServiceClass(std::unique_ptr<TaskRepositoryInterface> taskRepository);

 private:

/*
 * Converts from vector of TaskEntities to vector of TaskDTO
 *
 * @param: std::vector of TaskEntity
 *
 * @return-type: std::vector of TaskDTO
 */
  std::vector<TaskDTO>      MakeTasksDTO(const std::vector<TaskEntity>& tasksForDTO) const;

/*
 * Converts from vector of TaskEntities to vector of TaskDTO and sorts it by priority
 *
 * @param: std::vector of TaskEntity
 *
 * @return-type: std::vector of TaskDTO
 */
  std::vector<TaskDTO>      MakeTasksDTObyPriority(const std::vector<TaskEntity>& tasksForDTO) const;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
