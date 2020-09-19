//
// Created by valeriisudakov on 15.09.20.
//

#ifndef TASKMANAGER_CORE_API_TASKSERVICE_H_
#define TASKMANAGER_CORE_API_TASKSERVICE_H_

#include "TaskID.h"
#include "Date/Date.h"
#include "TaskDTO.h"
#include "AddTaskResult.h"
/*
*  Enter point to the program.
*
*  All requests to the system starts here.
*
*  @author: Valerii Sudakov
*/

class TaskService{
 public:
  virtual ~TaskService() = default;
/*
 * Add task to the system.
 *
 * @param: TaskDTO that contains info about task.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  virtual AddTaskResult             AddTask(const TaskDTO& task) = 0;
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
  virtual AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask) = 0;

  /*
  *  Remove Task from the system.
  *
  *  @param: TaskID that contains ID of task to delete
  *
  *  @return-type: true if task was deleted successfully, false if not
  */
  virtual bool                      RemoveTask(const TaskID& ID) = 0;

/*
 * Postpone task date;
 *
 * @param: TaskID that contains ID of task to postpone.
 * @param: Date that contains new date of task (postpone).
 *
 * @return-type: true if task was found and postponed, false if not
 */
  virtual bool                      PostponeTask(const TaskID& ID, const Date& date) = 0;

/*
 * Complete task;
 *
 * @param: TaskID that contains ID of task to complete.
 *
 * @return-type: true if task was found and completed, false if not
 */
  virtual bool                      SetTaskComplete(const TaskID& ID) = 0;

 public:

/*
 *  Returns task as TaskDTO from the system by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: if task exist - return value of TaskDTO, std::nullopt if not.
 */
  virtual std::optional<TaskDTO>    GetTask(const TaskID& id) const = 0;

/*
 *  Returns subtasks of task as a vector of TaskDTO from the system by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>    GetSubtask(const TaskID& id) const = 0;
/*
 * Returns all tasks from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>      GetTasks(bool byPriority) const = 0;

/*
 * Returns all tasks for today from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>      GetTodayTasks(bool byPriority) const = 0;

/*
 * Returns all tasks for this week from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>      GetWeekTasks(bool byPriority) const = 0;

/*
 * Returns all tasks by label from the systems
 *
 * @param: label - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const = 0;

/*
 * Returns all tasks by label from the systems
 *
 * @param: name - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>      GetTasksByName(const std::string& name, bool byPriority) const = 0;

/*
 * Returns all tasks by priority from the systems
 *
 * @param: label - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskDTO.
 */
  virtual std::vector<TaskDTO>      GetTasksByPriority(const Priority& priority) const = 0;
};

#endif //TASKMANAGER_CORE_API_TASKSERVICE_H_
