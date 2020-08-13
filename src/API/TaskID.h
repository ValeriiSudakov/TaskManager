//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKID_H_
#define TASKMANAGER_SRC_TASKID_H_
#include <cstdint>

class TaskID {
 public:
  TaskID(std::uint32_t ID);
  TaskID();

 public:
  std::uint32_t Get() const;

 private:
  std::uint32_t id_;
};

bool operator==(const TaskID& id1, const TaskID& id2);
bool operator!=(const TaskID& id1, const TaskID& id2);
bool operator<(const TaskID& id1, const TaskID& id2);
bool operator>(const TaskID& id1, const TaskID& id2);

#endif //TASKMANAGER_SRC_TASKID_H_
