//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "TaskID.h"
#include "Date/Date.h"
#include "TaskDTO.h"
#include "Memory_Model/Storage/TaskRepository.h"
#include "Memory_Model/Convertor.h"

/*
 *  Enter point to the program.
 *
 *  All requests to the system starts here.
 *
 *  @author: Valerii Sudakov
 */
class TaskService {
 public:
  static TaskService Create();
 public:

/*
 * Add task to the system.
 *
 * @param: TaskDTO that contains info about task.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  AddTaskResult             AddTask(const TaskDTO& task);
/*
 * Add subtask to the system.
 *
 * @param: TaskID that contains ID of root task.
 *
 * @param: TaskDTO that contains info about subtask.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask);

 /*
 *  Remove Task from the system.
 *
 *  @param: TaskID that contains ID of task to delete
 *
 *  @return-type: true if task was deleted successfully, false if not
 */
  bool                      RemoveTask(const TaskID& ID);

/*
 * Postpone task date;
 *
 * @param: TaskID that contains ID of task to postpone.
 * @param: Date that contains new date of task (postpone).
 *
 * @return-type: true if task was found and postponed, false if not
 */
  bool                      PostponeTask(const TaskID& ID, const Date& date);

/*
 * Complete task;
 *
 * @param: TaskID that contains ID of task to complete.
 *
 * @return-type: true if task was found and completed, false if not
 */
  bool                      SetTaskComplete(const TaskID& ID);
 public:

/*
 *  Returns task as TaskDTO from the system by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: if task exist - return value of TaskDTO, std::nullopt if not.
 */
  std::optional<TaskDTO>    GetTask(const TaskID& id) const;

/*
 *  Returns subtasks of task as a vector of TaskDTO from the system by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: vector of TaskDTO.
 */
  std::vector<TaskDTO>    GetSubtask(const TaskID& id) const;
/*
 * Returns all tasks from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  std::vector<TaskDTO>      GetTasks(bool byPriority) const;

/*
 * Returns all tasks for today from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  std::vector<TaskDTO>      GetTodayTasks(bool byPriority) const;

/*
 * Returns all tasks for this week from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  std::vector<TaskDTO>      GetWeekTasks(bool byPriority) const;

/*
 * Returns all tasks by label from the systems
 *
 * @param: label - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  std::vector<TaskDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const;

/*
 * Returns all tasks by label from the systems
 *
 * @param: name - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  std::vector<TaskDTO>      GetTasksByName(const std::string& name, bool byPriority) const;

/*
 * Returns all tasks by priority from the systems
 *
 * @param: label - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  std::vector<TaskDTO>      GetTasksByPriority(const Priority& priority) const;

 private:

  std::unique_ptr<TaskRepositoryInterface>            tasksRepository_;

  TaskService(std::unique_ptr<TaskRepositoryInterface> taskRepository);

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
