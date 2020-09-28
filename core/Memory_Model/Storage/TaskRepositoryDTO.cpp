//
// Created by valeriisudakov on 28.09.20.
//

#include "TaskRepositoryDTO.h"

TaskRepositoryDTO::TaskRepositoryDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                                     bool taskComplete, const TaskID &taskId, const TaskID& rootID)
    : name_(name), label_(label), Priority_(priority), date_(date), taskComplete_(taskComplete), taskID_(taskId), rootID_(rootID) {}


TaskRepositoryDTO::TaskRepositoryDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date)
    : name_(name), label_(label), Priority_(priority), date_(date), taskComplete_(false), taskID_(TaskID()), rootID_(taskID_) {}


std::optional<TaskRepositoryDTO> TaskRepositoryDTO::Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                                      bool taskComplete, const TaskID &taskId, const TaskID& rootID){
  if (name.empty() || label.empty()){
    return std::nullopt;
  }
  return TaskRepositoryDTO(name, label, priority, date, taskComplete, taskId, rootID);
}

std::optional<TaskRepositoryDTO> TaskRepositoryDTO::Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date){
  if (name.empty() || label.empty()){
    return std::nullopt;
  }
  return TaskRepositoryDTO(name, label, priority, date);
}

const std::string TaskRepositoryDTO::GetName() const {
  return name_;
}
const std::string TaskRepositoryDTO::GetLabel() const {
  return label_;
}
const Priority TaskRepositoryDTO::GetPriority() const{
  return Priority_;
}
const Date TaskRepositoryDTO::GetDate() const {
  return date_;
}
bool TaskRepositoryDTO::Complete() const {
  return taskComplete_;
}
const TaskID TaskRepositoryDTO::GetID() const {
  return taskID_;
}
