//
// Created by R2D2 on 16.07.2020.
//

#include "TaskID.h"

TaskID::TaskID() :ID(0) {}
TaskID::~TaskID() = default;
unsigned int TaskID::CreateID(){
  return ID++;
}