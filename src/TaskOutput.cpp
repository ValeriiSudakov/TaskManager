//
// Created by R2D2 on 17.07.2020.
//

#include "TaskOutput.h"

TaskOutput::TaskOutput() {};
TaskOutput::~TaskOutput() = default;

void TaskOutput::Print(const Task& task) const{
  std::cout<<"Task name: "<<task.GetName()<<std::endl;
  std::cout<<"Task label: "<<task.GetLabel()<<std::endl;
  std::cout<<"Task priority: "<<GetTaskPriorityStr(task.GetPriority())<<std::endl;
  std::cout<<"Task due date: ";
  PrintTaskDueDateStr(task.GetDueDate());
}

const std::string TaskOutput::GetTaskPriorityStr(const Task::Priority& priority) const{
  if (priority == Task::Priority::HIGH){ return "High"; }
  else if (priority == Task::Priority::LOW){ return "Low"; }
  else if (priority == Task::Priority::NONE){ return "None"; }
  else return "";
}

void TaskOutput::PrintTaskDueDateStr(const tm& date) const{
  std::cout << "Year:"  << 1900 + date.tm_year << std::endl;
  std::cout << "Month: "<< 1 + date.tm_mon<< std::endl;
  std::cout << "Day: "  <<  date.tm_mday << std::endl;
  std::cout << "Time: " << 1 + date.tm_hour << ":"
            << 1 + date.tm_min << ":"
            << 1 + date.tm_sec << std::endl;
}