//
// Created by valeriisudakov on 15.09.20.
//

#ifndef TASKMANAGER_CORE_API_TASKSERVICE_H_
#define TASKMANAGER_CORE_API_TASKSERVICE_H_

#include "TaskID.h"
#include "Date.h"
#include "TaskServiceDTO.h"
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
 * @param: TaskServiceDTO that contains info about task.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  virtual AddTaskResult             AddTask(const TaskServiceDTO& task) = 0;
/*
 * Add subtask to the system.
 *
 * @param: TaskID that contains ID of root task.
 *
 * @param: TaskServiceDTO that contains info about subtask.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  virtual AddTaskResult             AddSubtask(const TaskID& rootTaskID, const TaskServiceDTO& subtask) = 0;

/*
 * Load all task to the system.
 *
 * @param: file name to load tasks
 *
 * @return-type: true if success, false if not.
 */
  virtual bool                      Load(const std::string& filename) = 0;

/*
 * Save all task of the system.
 *
 * @param: file name to save tasks
 *
 * @return-type: true if success, false if not.
 */
  virtual bool                      Save(const std::string& filename) = 0;

  /*
  *  Remove Task from the system.
  *
  *  @param: TaskID that contains ID of task to delete
  *
  *  @return-type: true if task was deleted successfully, false if not
  */
  virtual bool                      RemoveTask(const TaskID& ID) = 0;

/*
 * Postpone task date
 *
 * @param: TaskID that contains ID of task to postpone.
 * @param: Date that contains new date of task (postpone).
 *
 * @return-type: true if task was found and postponed, false if not
 */
  virtual bool                      PostponeTask(const TaskID& ID, const Date& date) = 0;

/*
 * Complete task
 *
 * @param: TaskID that contains ID of task to complete.
 *
 * @return-type: true if task was found and completed, false if not
 */
  virtual bool                      SetTaskComplete(const TaskID& ID) = 0;

 public:

/*
 *  Returns task as TaskServiceDTO from the system by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: if task exist - return value of TaskServiceDTO, std::nullopt if not.
 */
  virtual std::optional<TaskServiceDTO>    GetTask(const TaskID& id) const = 0;

/*
 *  Returns subtasks of task as a vector of TaskServiceDTO from the system by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>    GetSubtask(const TaskID& id) const = 0;
/*
 * Returns all tasks from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>      GetTasks(bool byPriority) const = 0;

/*
 * Returns all tasks for today from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>      GetTodayTasks(bool byPriority) const = 0;

/*
 * Returns all tasks for this week from the systems
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>      GetWeekTasks(bool byPriority) const = 0;

/*
 * Returns all tasks by label from the systems
 *
 * @param: label - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const = 0;

/*
 * Returns all tasks by name from the systems
 *
 * @param: name - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>      GetTasksByName(const std::string& name, bool byPriority) const = 0;

/*
 * Returns all tasks by priority from the systems
 *
 * @param: priority - search criteria for tasks in the system
 * @param byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskServiceDTO.
 */
  virtual std::vector<TaskServiceDTO>      GetTasksByPriority(const Priority& priority) const = 0;
};

#endif //TASKMANAGER_CORE_API_TASKSERVICE_H_
