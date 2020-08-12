//
// Created by R2D2 on 29.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKDTO_H_
#define TASKMANAGER_SRC_TASKDTO_H_
#include "Memory_Model/Task/TaskEntity.h"
#include "Date/Date.h"
class TaskDTO {
 public:
    TaskDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
            bool taskComplete, const TaskID &taskId);
 public:
  static TaskDTO        CreateFromTask(const Task& task);
  static TaskDTO        CreateFromTaskEntity(const TaskEntity& taskEntity);

public:
  const std::string&    GetName() const;
  const std::string&    GetLabel() const;
  const Priority&       GetPriority() const;
  const Date&           GetDate() const;
  bool                  IsTaskComplete() const;
  const TaskID&         GetTaskId() const;

 private:
  std::string   name_;
  std::string   label_;
  Priority      Priority_;
  Date          date_;
  bool          taskComplete_;
  TaskID        taskID_;
};

#endif //TASKMANAGER_SRC_TASKDTO_H_
