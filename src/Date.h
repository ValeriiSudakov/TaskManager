//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_DATE_H_
#define TASKMANAGER_SRC_DATE_H_
#include <ctime>
#include <stdexcept>

namespace Date{
  tm GetCurrentTime();
  tm CreateDate(int date, int month, int year, int weekDay);
};

#endif //TASKMANAGER_SRC_DATE_H_
