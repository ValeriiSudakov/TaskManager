//
// Created by R2D2 on 16.07.2020.
//

#include "TaskID.h"

TaskID::TaskID() :ID(0) {}
TaskID::TaskID(unsigned int id) : ID(id) {}
TaskID::~TaskID() = default;


unsigned int TaskID::GenerateID() {
  return ID++;
}

unsigned int TaskID::GetID() const {
  return ID;
}
