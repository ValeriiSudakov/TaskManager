//
// Created by R2D2 on 16.07.2020.
//

#include "TaskID.h"

TaskID::TaskID(unsigned int ID) : id_(ID) {}

TaskID::TaskID() : id_(0){}

unsigned int TaskID::Get() const {
  return id_;
}

bool operator==(const TaskID& id1, const TaskID& id2){
  return id1.Get() == id2.Get();
}

bool operator!=(const TaskID& id1, const TaskID& id2){
  return id1.Get() != id2.Get();
};

bool operator<(const TaskID& id1, const TaskID& id2){
  return id1.Get() < id2.Get();
}

bool operator>(const TaskID& id1, const TaskID& id2){
  return id1.Get() > id2.Get();
}

