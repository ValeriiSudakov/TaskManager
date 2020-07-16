//
// Created by R2D2 on 16.07.2020.
//

#include "Date.h"

Date::Date() : dueDate(tm()) {}

Date::~Date() = default;

tm Date::GetDate() const{
  return dueDate;
}