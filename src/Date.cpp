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
  // decrease year for compare by mktime
  if (date.tm_year == 2020) {
    date.tm_year -= 1900;
  }
  return mktime(&currentDate) <= mktime(&date) &&
        mktime(&date) <= mktime(&endOfWeek);
}

void Date::PrintDate(const tm& date){
  std::cout << "Year:"  << 1900 + date.tm_year << std::endl;
  std::cout << "Month: "<< 1 + date.tm_mon<< std::endl;
  std::cout << "Day: "  <<  date.tm_mday << std::endl;
  std::cout << "Time: " << 1 + date.tm_hour << ":"
            << 1 + date.tm_min << ":"
            << 1 + date.tm_sec << std::endl;
}