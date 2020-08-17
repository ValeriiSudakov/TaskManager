//
// Created by R2D2 on 29.07.2020.
//

#include "TaskDTO.h"

TaskDTO::TaskDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                 bool taskComplete, const TaskID &taskId)
                 : name_(name), label_(label), Priority_(priority), date_(date), taskComplete_(taskComplete), taskID_(taskId) {}


TaskDTO::TaskDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date)
  : name_(name), label_(label), Priority_(priority), date_(date), taskComplete_(false), taskID_(TaskID()){}


TaskDTO TaskDTO::Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                                      bool taskComplete, const TaskID &taskId){
  return TaskDTO(name, label, priority, date, taskComplete, taskId);
}

TaskDTO TaskDTO::Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date){
  return TaskDTO(name, label, priority, date);
}

const std::string TaskDTO::GetName() const {
  return name_;
}
const std::string TaskDTO::GetLabel() const {
  return label_;
}
const Priority TaskDTO::GetPriority() const{
  return Priority_;
}
const Date TaskDTO::GetDate() const {
  return date_;
}
bool TaskDTO::IsTaskComplete() const {
  return taskComplete_;
}
const TaskID TaskDTO::GetTaskId() const {
  return taskID_;
}

