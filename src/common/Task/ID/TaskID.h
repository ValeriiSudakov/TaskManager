//
// Created by valeriisudakov on 16.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKID_H_
#define TASKMANAGER_SRC_TASKID_H_
#include <cstdint>

/*
 *  Class-wrapper of ID to hide its implementation
 *
 *  @author: Valerii Sudakov
 */
class TaskID {
 public:
  TaskID(std::uint32_t ID);
  TaskID();

 public:
/*
 * @return-type value of id_
 */
  std::uint32_t Get() const;

 private:
  std::uint32_t id_;
};

/*
 * Compare operators.
 *
 * @param: TaskID
 *
 * @return-type: result of compare id1 and id2
 */
bool operator==(const TaskID& id1, const TaskID& id2);
bool operator!=(const TaskID& id1, const TaskID& id2);
bool operator<(const TaskID& id1, const TaskID& id2);
bool operator>(const TaskID& id1, const TaskID& id2);

#endif //TASKMANAGER_SRC_TASKID_H_
