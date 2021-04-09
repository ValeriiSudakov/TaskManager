//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
#include "AddTaskResult.h"
#include "TaskRepositoryDTO.h"
#include "Priority.h"

/*
 * Tasks repository interface.
 *
 * @author: Valerii Sudakov.
 */
class TaskRepository{
 public:
  virtual ~TaskRepository() = default;

 public:
/*
 * Add task to the repository.
 *
 * @param: TaskRepositoryDTO that contains info about task.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  virtual AddTaskResult                       AddTask(const TaskRepositoryDTO& task) = 0;

/*
 * Add subtask to the repository.
 *
 * @param: TaskID that contains ID of root task.
 *
 * @param: TaskRepositoryDTO that contains info about subtask.
 * Only the members of the class will be used: name, label, Priority and Date.
 *
 * @return-type: AddTaskResult that contains info about result of operation.
 */
  virtual AddTaskResult                       AddSubtask(const TaskID& rootTaskID, const TaskRepositoryDTO& subtask) = 0;

/*
 *  Remove Task from the repository.
 *
 *  @param: TaskID that contains ID of task to delete
 *
 *  @return-type: true if task was deleted successfully, false if not
 */
  virtual bool                                RemoveTask(const TaskID& id) = 0;

/*
 * Postpone task date;
 *
 * @param: TaskID that contains ID of task to postpone.
 * @param: Date that contains new date of task (postpone).
 *
 * @return-type: true if task was found and postponed, false if not
 */
  virtual bool                                PostponeTask(const TaskID& id, const Date& date) = 0;

/*
 * Complete task
 *
 * @param: TaskID that contains ID of task to complete.
 *
 * @return-type: true if task was found and completed, false if not
 */
  virtual bool                                SetTaskComplete(const TaskID& id) = 0;

/*
 *  Returns task as TaskRepositoryDTO from the repository by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: if task exist - return value of TaskRepositoryDTO, std::nullopt if not.
 */
  virtual std::optional<TaskRepositoryDTO>    GetTask(const TaskID& id) const = 0;

/*
 *  Returns subtasks of task as a vector of TaskRepositoryDTO from the repository by ID.
 *
 *  @param: TaskID that contains ID of task to return.
 *
 *  @return-type: vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetSubtask(const TaskID& id) const = 0;

/*
 * Returns all tasks from the repository.
 *
 * @return-type: std::vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetTasks() const = 0;

/*
 * Returns all tasks for today from the repository.
 *
 * @return-type: std::vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetTodayTasks(bool byPriority) const = 0;

/*
 * Returns all tasks for this week from the repository.
 *
 * @param: byPriority. if true - returned tasks will be sorted by priority, not if false.
 *
 * @return-type: std::vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetWeekTasks(bool byPriority) const = 0;

/*
 * Returns all tasks by label from the repository.
 *
 * @param: label - search criteria for tasks in the system
 *
 * @return-type: std::vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const = 0;

/*
 * Returns all tasks by name from the repository.
 *
 * @param: name - search criteria for tasks in the system
 *
 * @return-type: std::vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetTasksByName(const std::string& name, bool byPriority) const = 0;

/*
 * Returns all tasks by priority from the repository.
 *
 * @param: priority - search criteria for tasks in the system
 *
 * @return-type: std::vector of TaskRepositoryDTO.
 */
  virtual std::vector<TaskRepositoryDTO>      GetTasksByPriority(const Priority& priority) const = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKREPOSITORYINTERFACE_H_
