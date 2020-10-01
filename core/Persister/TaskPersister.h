//
// Created by valeriisudakov on 29.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_TASKPERSISTER_H_
#define TASKMANAGER_CORE_PERSISTER_TASKPERSISTER_H_
#include "SerializedModel.pb.h"
#include "Persister.h"
#include "Memory_Model/Storage/TaskRepository.h"
#include "fstream"

class TaskPersister : public Persister{
 public:
  TaskPersister(TaskRepository& repository, std::fstream& file)
    : repository_(repository) {
      std::swap(file, file_);
  }


 public:
  bool Load() override;
  bool Save() override;

 private:
  std::fstream file_;
  TaskRepository& repository_;
};

#endif //TASKMANAGER_CORE_PERSISTER_TASKPERSISTER_H_
