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
  tm    CreateDate(int date, int month, int year, int weekDay);
  bool  IsToday(const tm& date);
  bool  IsThisWeek(tm date);
  void  PrintDate(const tm& date);
};

#endif //TASKMANAGER_SRC_DATE_H_