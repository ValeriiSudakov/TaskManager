//
// Created by valeriisudakov on 28.09.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYDTO_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYDTO_H_

#include "Date.h"
#include "TaskID.h"
#include "Priority.h"
#include <optional>

/*
 * DTO TaskRepository information.
 *
 * @author: Valerii Sudakov
 */
class TaskRepositoryDTO {

 public:

/*
 * Create DTO based on the Task.
 *
 * @return-type: TaskRepositoryDTO
 */
  static std::optional<TaskRepositoryDTO>        Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date);

/*
 * Create DTO based on the TaskEntity.
 *
 * @return-type: TaskRepositoryDTO
 */
  static std::optional<TaskRepositoryDTO>        Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                                         bool taskComplete, const TaskID &taskId, const TaskID& rootID);

 public:
  const std::string               GetName() const;
  const std::string               GetLabel() const;
  const Priority                  GetPriority() const;
  const Date                      GetDate() const;
  bool                            Complete() const;
  const TaskID                    GetID() const;
  const TaskID                    GetRootID() const;

 private:
  std::string                     name_;
  std::string                     label_;
  Priority                        Priority_;
  Date                            date_;
  bool                            taskComplete_;
  TaskID                          taskID_;
  TaskID                          rootID_;

 private:
  TaskRepositoryDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date);

  TaskRepositoryDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                 bool taskComplete, const TaskID &taskId, const TaskID& rootID);
};

#endif //TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_TASKREPOSITORYDTO_H_
