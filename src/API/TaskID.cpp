//
// Created by R2D2 on 16.07.2020.
//

#include "TaskID.h"

TaskID::TaskID(unsigned int ID) : id_(ID) {}

TaskID::TaskID() : id_(0){}

unsigned int TaskID::GetID() const {
  return id_;
}
