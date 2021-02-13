//
// Created by R2D2 on 16.07.2020.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

Date::Date(std::string date) : date_(boost::gregorian::from_string(date)){}
Date::Date(boost::gregorian::date date) : date_(date) { }
Date::Date() : date_(boost::gregorian::date() ) { }

boost::gregorian::date Date::GetCurrentTime(){
  return boost::gregorian::day_clock::local_day();
}

boost::gregorian::date Date::Get() const{
  return date_;
}

std::string Date::ToString() const {
  return boost::gregorian::to_iso_extended_string(date_);
}

bool Date::IsThisWeek(const boost::gregorian::date &day) {
    return (Date::BeginOfWeek() <= day.day_number() && day.day_number() <= Date::EndOfWeek());
}

bool Date::IsToday(const boost::gregorian::date& day) {
  return Date::GetCurrentTime().day_number() == day.day_number();
}

std::uint32_t Date::EndOfWeek(){
        /** days of week begins from 0 - sunday **/
  auto currentDate = Date::GetCurrentTime();
  auto dayOfWeek = currentDate.day_of_week();
  return (dayOfWeek == 0 ? currentDate.day_number() : currentDate.day_number() + 7 - dayOfWeek);
}

std::uint32_t Date::BeginOfWeek(){
          /** days of week begins from 0 - sunday **/
    auto currentDate = Date::GetCurrentTime();
    return currentDate.day_number() - currentDate.day_of_week() + 1;
}
