//
// Created by valeriisudakov on 16.07.2020.
//

#include "TaskID.h"

TaskID::TaskID(std::uint32_t ID) : id_(ID) {}

TaskID::TaskID() : id_(0){}

std::uint32_t TaskID::Get() const {
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

