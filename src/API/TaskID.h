//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKID_H_
#define TASKMANAGER_SRC_TASKID_H_


class TaskID {
 public:
  TaskID(unsigned int ID);
  TaskID();

 public:
  unsigned int Get() const;

 private:

  unsigned int id_;
};

bool operator==(const TaskID& id1, const TaskID& id2);
bool operator!=(const TaskID& id1, const TaskID& id2);
bool operator<(const TaskID& id1, const TaskID& id2);
bool operator>(const TaskID& id1, const TaskID& id2);

#endif //TASKMANAGER_SRC_TASKID_H_
