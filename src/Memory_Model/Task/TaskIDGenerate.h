//
// Created by R2D2 on 30.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKIDGENERATE_H_
#define TASKMANAGER_SRC_TASKIDGENERATE_H_
#include "API/TaskID.h"

class TaskIDGenerate {
 public:
  TaskIDGenerate();
  TaskID Generate();

 private:
  std::uint32_t id_;
};

#endif //TASKMANAGER_SRC_TASKIDGENERATE_H_
