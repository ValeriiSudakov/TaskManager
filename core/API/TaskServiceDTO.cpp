//
// Created by R2D2 on 29.07.2020.
//

#include "TaskServiceDTO.h"

TaskServiceDTO::TaskServiceDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                               bool taskComplete, const TaskID &taskId)
                 : name_(name), label_(label), Priority_(priority), date_(date), taskComplete_(taskComplete), taskID_(taskId) {}


TaskServiceDTO::TaskServiceDTO(const std::string &name, const std::string &label, const Priority &priority, const Date &date)
  : name_(name), label_(label), Priority_(priority), date_(date), taskComplete_(false), taskID_(TaskID()){}


TaskServiceDTO TaskServiceDTO::Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date,
                                      bool taskComplete, const TaskID &taskId){
  return TaskServiceDTO(name, label, priority, date, taskComplete, taskId);
}

TaskServiceDTO TaskServiceDTO::Create(const std::string &name, const std::string &label, const Priority &priority, const Date &date){
  return TaskServiceDTO(name, label, priority, date);
}

const std::string TaskServiceDTO::GetName() const {
  return name_;
}
const std::string TaskServiceDTO::GetLabel() const {
  return label_;
}
const Priority TaskServiceDTO::GetPriority() const{
  return Priority_;
}
const Date TaskServiceDTO::GetDate() const {
  return date_;
}
bool TaskServiceDTO::IsTaskComplete() const {
  return taskComplete_;
}
const TaskID TaskServiceDTO::GetTaskId() const {
  return taskID_;
}

const std::string TaskServiceDTO::PriorityToString() const {
  if (Priority_ == Priority::FIRST){
    return "first";
  } else if (Priority_ == Priority::SECOND){
    return "second";
  } else if (Priority_ == Priority::THIRD){
    return "third";
  } else {
    return "none";
  }
}

const std::string TaskServiceDTO::ToString() const {
  std::string result;
  std::string priority = PriorityToString();
  result += "Task name: " + name_ + "\nTask label: " + label_ + "\nTask priority: " + priority
          + (taskComplete_ ? "\nCompleted" : "\nNot completed") + "\nDate: " + date_.ToString();
  return result;
}

