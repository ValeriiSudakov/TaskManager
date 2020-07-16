//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_DATE_H_
#define TASKMANAGER_SRC_DATE_H_
#include <ctime>
#include <stdexcept>

class Date {
 public:
  tm dueDate;
 public:
  Date();
  ~Date();
  tm GetDate() const;
};

#endif //TASKMANAGER_SRC_DATE_H_
