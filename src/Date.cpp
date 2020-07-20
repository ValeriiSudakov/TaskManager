//
// Created by R2D2 on 16.07.2020.
//

#include "Date.h"

tm Date::GetCurrentTime() {
  std::time_t t = std::time(0);   // get time now
  std::tm* now = std::localtime(&t);
  return *now;
}

tm Date::CreateDate(int date, int month, int year, int weekDay){
  if (date < 1 || date > 31){
    throw std::runtime_error{"Incorrect date"};
  }
  if (month < 0 || month > 11){
    throw std::runtime_error{"Incorrect month"};
  }
  if (year != 2020){
    throw std::runtime_error{"Incorrect year"};
  }
  if (weekDay < 0 || weekDay > 6) {
    throw std::runtime_error{"Incorrect week day"};
  }
  tm dueDate = tm();
  dueDate.tm_mday = date;
  dueDate.tm_mon = month;
  dueDate.tm_year = year;
  dueDate.tm_wday = weekDay;
  return dueDate;
}