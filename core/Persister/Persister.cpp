//
// Created by valeriisudakov on 29.09.20.
//

#include "Persister.h"
#include "API/Priority.h"

SerializePriority DataPersister::PriorityToSerializedPriority(const Priority& priority){
  if (Priority::FIRST == priority){
    return SerializePriority::FIRST;
  } else if (Priority::SECOND == priority){
    return SerializePriority::SECOND;
  } else if (Priority::THIRD == priority){
    return SerializePriority::THIRD;
  } else if (Priority::NONE == priority) {
    return SerializePriority::NONE;
  }
}

Priority DataPersister::SerializedPriorityToPriority(const SerializePriority& priority){
  if (SerializePriority::FIRST == priority){
    return Priority::FIRST;
  } else if (SerializePriority::SECOND == priority){
    return Priority::SECOND;
  } else if (SerializePriority::THIRD == priority){
    return Priority::THIRD;
  } else if (SerializePriority::NONE == priority) {
    return Priority::NONE;
  }
}