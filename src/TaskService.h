//
// Created by R2D2 on 15.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKSERVICE_H_
#define TASKMANAGER_SRC_TASKSERVICE_H_
#include "FullTask.h"
#include "TaskID.h"
#include "Date.h"

#include <map>

class TaskService {
 public:
  TaskService();
  ~TaskService();

 public:
  void AddTask(const Task& task, const Task::Priority& priority);
  void AddSubtask(unsigned int rootTaskID, const Task& subtask,const Task::Priority& priority);

  std::shared_ptr<TaskEntity> GetTaskByName(const std::string& name) const; //for test

  unsigned int GetTaskIDByName(const std::string& name) const;


  static Date CreateDate(int date, int month, int year, int weekDay){
    if (date < 1 || date > 31){
      throw std::runtime_error{"Incorrect date"};
    }
    if (month < 0 || date > 11){
      throw std::runtime_error{"Incorrect month"};
    }
    if (year != 2020){
      throw std::runtime_error{"Incorrect year"};
    }
    if (weekDay < 0 || weekDay > 6) {
      throw std::runtime_error{"Incorrect week day"};
    }
    Date datetime;
    datetime.dueDate.tm_mday = date;
    datetime.dueDate.tm_mon = month;
    datetime.dueDate.tm_year = year;
    datetime.dueDate.tm_wday = weekDay;
    return datetime;
  }

 private:
  std::vector<std::shared_ptr<FullTask>> tasks;
  std::multimap<Task::Priority, std::weak_ptr<TaskEntity>> byPriority;
  TaskID taskID;
};

#endif //TASKMANAGER_SRC_TASKSERVICE_H_
