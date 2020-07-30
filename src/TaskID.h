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
  unsigned int GetID() const;

 private:
  unsigned int id_;
};

#endif //TASKMANAGER_SRC_TASKID_H_
