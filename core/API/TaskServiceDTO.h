//
// Created by R2D2 on 29.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKDTO_H_
#define TASKMANAGER_SRC_TASKDTO_H_
#include "Date/Date.h"
#include "TaskID.h"
#include "Priority.h"

/*
 * DTO TaskService information.
 *
 * @author: Valerii Sudakov
 */
class TaskServiceDTO {

 public:

/*
 * Create DTO based on the Task.
 *
 * @return-type: TaskServiceDTO
 */
  static TaskServiceDTO        Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date);

/*
 * Create DTO based on the TaskEntity.
 *
 * @return-type: TaskServiceDTO
 */
  static TaskServiceDTO        Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                                      bool taskComplete, const TaskID &taskId);

public:
  const std::string            GetName() const;
  const std::string            GetLabel() const;
  const Priority               GetPriority() const;
  const Date                   GetDate() const;
  bool                         IsTaskComplete() const;
  const TaskID                 GetTaskId() const;
  const std::string            ToString() const;

 private:
  std::string                  name_;
  std::string                  label_;
  Priority                     Priority_;
  Date                         date_;
  bool                         taskComplete_;
  TaskID                       taskID_;

 private:
  TaskServiceDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date);

  TaskServiceDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                 bool taskComplete, const TaskID &taskId);

  const std::string PriorityToString() const;
};

#endif //TASKMANAGER_SRC_TASKDTO_H_
