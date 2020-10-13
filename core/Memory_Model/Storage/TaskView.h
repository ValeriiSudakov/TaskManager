//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKVIEWINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKVIEWINTERFACE_H_

#include "Memory_Model/Task/TaskEntity.h"
#include "API/Priority.h"
#include <map>
#include <vector>

/*
 * TaskView interface.
 * Provides method to use view.
 * Class will contains sorted tasks by: name, label, priority and date.
 *
 * @author: Valerii Sudakov.
 */
class TaskView {
 public:
 virtual ~TaskView() = default;

 public:

/*
 * Add task to View.
 *
 * @param: weak ptr to task.
 */
  virtual void                      AddTask(const std::weak_ptr<TaskEntity> &task) = 0;

/*
 * Remove task from view.
 *
 * @param: weak ptr to task.
 */
  virtual bool                      RemoveTask(const std::weak_ptr<TaskEntity> &task) = 0;

 public:

/*
 * Get tasks method. Return all tasks sorted by date.
 *
 * @return-type: vector of TaskEntity.
 */
  virtual std::vector<TaskEntity>   GetTasks() const = 0;

/*
 * Get tasks method. Return all tasks for today.
 *
 * @return-type: vector of TaskEntity.
 */
  virtual std::vector<TaskEntity>   GetTodayTasks() const = 0;

/*
 * Get tasks method. Return all tasks for this week since today.
 *
 * @return-type: vector of TaskEntity.
 */
  virtual std::vector<TaskEntity>   GetWeekTasks() const = 0;

/*
 * Get tasks method. Return all tasks sorted by label.
 *
 * @param: label of task
 *
 * @return-type: vector of TaskEntity.
 */
  virtual std::vector<TaskEntity>   GetTasksByLabel(const std::string &label) const = 0;

/*
 * Get tasks method. Return all tasks sorted by name.
 *
 * @param: name of task
 *
 * @return-type: vector of TaskEntity.
 */
  virtual std::vector<TaskEntity>   GetTasksByName(const std::string &name) const = 0;

/*
 * Get tasks method. Return all tasks sorted by priority.
 *
 * @param: priority of task
 *
 * @return-type: vector of TaskEntity.
 */
  virtual std::vector<TaskEntity>   GetTasksByPriority(Priority taskPriority) const = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKVIEWINTERFACE_H_
