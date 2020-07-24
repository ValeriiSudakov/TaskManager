//
// Created by R2D2 on 17.07.2020.
//

#include "TaskOutput.h"
#include "Date.h"

TaskOutput::TaskOutput() {};
TaskOutput::~TaskOutput() = default;

void TaskOutput::Print(const std::vector<Task>& tasks) const{
  for (auto task : tasks){
    std::cout<<"Task name: "<<task.GetName()<<std::endl;
    std::cout<<"Task label: "<<task.GetLabel()<<std::endl;
    std::cout<<"Task priority: "<<GetTaskPriorityStr(task.GetPriority())<<std::endl;
    std::cout<<"Task due date: ";
    Date::PrintDate(task.GetDueDate());
  }
}

const std::string TaskOutput::GetTaskPriorityStr(const Task::Priority& priority) const{
  if (priority == Task::Priority::HIGH){ return "High"; }
  else if (priority == Task::Priority::LOW){ return "Low"; }
  else if (priority == Task::Priority::NONE){ return "None"; }
  else return "";
}
