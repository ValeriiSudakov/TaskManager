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

/*
 * Class-wrapper to boost::gregorian::date
 *
 * @author: Valerii Sudakov
 */
class Date{
 public:
  Date(std::string date);
  Date(boost::gregorian::date date);
  Date();

 public:

/*
 * Returns object that contains current date
 *
 * @return-type: boost::gregorian::date object
 */
  static boost::gregorian::date     GetCurrentTime();

  boost::gregorian::date            Get() const;

/*
 * Convert boost::gregorian::date to std::string
 *
 * @return-type: std::string object
 */
  std::string                       ToString() const;

 public:

/*
 * Checks is this week contains input date or not
 *
 * @param: day that contains info about date to check
 *
 * @return-type: true if it is, false if not
 */
  static bool                       IsThisWeek(const boost::gregorian::date& day);

/*
 * Checks if the input date equals current day
 *
 * @param: day that contains info about date to check
 *
 * @return-type: true if it is, false if not
 */
  static bool                       IsToday(const boost::gregorian::date& day);

/*
 * Calculating and return week ends day
 *
 * @return-type: day number
 */
  static std::uint32_t              EndOfWeek();

/*
 * Calculating and return week begins day
 *
 * @return-type: day number
 */
    static std::uint32_t              BeginOfWeek();
 private:
  boost::gregorian::date date_;

};

#endif //TASKMANAGER_SRC_DATE_H_
