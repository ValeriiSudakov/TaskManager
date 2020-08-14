//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_DATE_H_
#define TASKMANAGER_SRC_DATE_H_
#include <ctime>
#include <cstdint>
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
  std::string                       ToString() const;

 public:
  static bool                       IsThisWeek(const boost::gregorian::date& day);
  static bool                       IsToday(const boost::gregorian::date& day);
  static std::uint32_t              DayForEndOfWeek();
 private:
  boost::gregorian::date date_;

};

#endif //TASKMANAGER_SRC_DATE_H_
