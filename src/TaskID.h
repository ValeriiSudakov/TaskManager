//
// Created by R2D2 on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKID_H_
#define TASKMANAGER_SRC_TASKID_H_


// таск гениратор
// подумать, как сделать это в мой стринг id
class TaskID {
 public:
  TaskID();
  ~TaskID();
  unsigned int CreateID();
 private:
  unsigned int ID;
};

#endif //TASKMANAGER_SRC_TASKID_H_
