//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_DATE_H_
#define TASKMANAGER_SRC_DATE_H_
#include <ctime>
#include <stdexcept>
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

class Date{
 public:
  Date(std::string date);
  Date(boost::gregorian::date date);

 public:
  static boost::gregorian::date     GetCurrentTime();
  boost::gregorian::date            Get() const;
  std::string                       ToString();

 public:
  static bool                       IsThisWeek(const boost::gregorian::date& day);
  static bool                       IsToday(const boost::gregorian::date& day);
  static unsigned int               DayForEndOfWeek();
 private:
  boost::gregorian::date date_;

};

#endif //TASKMANAGER_SRC_DATE_H_
