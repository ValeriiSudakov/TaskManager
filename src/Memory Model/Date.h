//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_DATE_H_
#define TASKMANAGER_SRC_DATE_H_
#include <ctime>
#include <stdexcept>
#include <iostream>

namespace Date{
  tm    GetCurrentTime();
  bool  IsToday(const tm& date);
  bool  IsThisWeek(tm date);
};

#endif //TASKMANAGER_SRC_DATE_H_
