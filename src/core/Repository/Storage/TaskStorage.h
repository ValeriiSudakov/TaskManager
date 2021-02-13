//
// Created by valeriisudakov on 13.08.20.
//

#ifndef TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKSTORAGEINTERFACE_H_
#define TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKSTORAGEINTERFACE_H_
#include "Repository/Task/TaskEntity.h"
#include "Repository/Task/ID/TaskIDGenerate.h"
#include <map>

/*
 * Task storage interface: provides method to store tasks.
 *
 * @author: Valerii Sudakov.
 */
class TaskStorage{
 public:
  virtual ~TaskStorage() = default;

 public:

/*
 * Returns all task.
 *
 * @return-type: const reference to the map with tasks: key - id of task, value - task.
 */
  virtual const std::map<TaskID, std::shared_ptr<TaskEntity>>&    GetTasks() const = 0;

/*
 * Return task by id.
 *
 * @param: TaskID of task.
 *
 * @return-type: shared ptr to task, if it exist, nullopt if not.
 */
  virtual std::optional<std::shared_ptr<TaskEntity>>              GetTask(const TaskID& taskID) const = 0;

/*
 * Add task.
 *
 * @param: TaskEntity to add.
 *
 * @return-type: shared ptr to task, if it were added, nullopt if not.
 */
  virtual std::optional<std::shared_ptr<TaskEntity>>              AddTask(const TaskEntity& task) = 0;

/*
 * Remove task.
 *
 * @param: TaskID of task to remove.
 *
 * @return-type: true if task were deleted, false if not.
 */
  virtual bool                                                    RemoveTask(const TaskID& id) = 0;
/*
 * Postpone task.
 *
 * @param: TaskID of task to postpone.
 * @param: new date to task.
 *
 * @return-type: true if task were postponed, false if not.
 */
  virtual bool                                                    PostponeTask(const TaskID& id, const Date& date) = 0;
};

#endif //TASKMANAGER_SRC_MEMORY_MODEL_STORAGE_TASKSTORAGEINTERFACE_H_
