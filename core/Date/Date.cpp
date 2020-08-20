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

bool Date::IsToday(const boost::gregorian::date& day) {
  return Date::GetCurrentTime().day_number() == day.day_number();
}

bool Date::IsThisWeek(const boost::gregorian::date& day){
  Date currentDate(Date::GetCurrentTime());
  int endOfWeek = DayForEndOfWeek();
  return currentDate.Get().day_number() <= day.day_number() && day.day_number() <= endOfWeek;
}

std::uint32_t Date::DayForEndOfWeek(){
  auto currentDate = Date::GetCurrentTime();
  auto dayOfWeek = currentDate.day_of_week();
  return dayOfWeek == 0 ? 0 : currentDate.day_number() + 7 - dayOfWeek;
}