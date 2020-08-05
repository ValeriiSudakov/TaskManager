//
// Created by R2D2 on 16.07.2020.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

tm Date::GetCurrentTime() {
  std::time_t t = std::time(0);   // get time now
  std::tm* now = std::localtime(&t);
  return *now;
}


bool Date::IsToday(const tm& date){
  tm currentDate = GetCurrentTime();

  return date.tm_mon == currentDate.tm_mon &&
        date.tm_mday == currentDate.tm_mday;
}

bool Date::IsThisWeek(tm date) {
  tm currentDate = GetCurrentTime();
  int daysToEndOfWeek = 7 - currentDate.tm_wday;
  tm endOfWeek = GetCurrentTime();
  // find the end of the week date
  if (currentDate.tm_mday + daysToEndOfWeek > 31){
    endOfWeek.tm_mday = (31 + daysToEndOfWeek) - 31;
    endOfWeek.tm_mon++;
  } else {
    endOfWeek.tm_mday = currentDate.tm_mday + daysToEndOfWeek;
    endOfWeek.tm_mon = currentDate.tm_mon;
  }
  return mktime(&currentDate) <= mktime(&date) &&
        mktime(&date) <= mktime(&endOfWeek);
}
