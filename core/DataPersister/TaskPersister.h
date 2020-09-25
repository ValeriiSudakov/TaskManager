//
// Created by valeriisudakov on 24.09.20.
//

#ifndef TASKMANAGER_CORE_DATAPERSISTER_TASKPERSISTER_H_
#define TASKMANAGER_CORE_DATAPERSISTER_TASKPERSISTER_H_
#include "DataPersister.h"

class TaskPersister : public DataPersister::Persister {
 public:
  bool Save(const std::string &fileName, TaskRepository &repository) override;
  bool Load(const std::string &fileName, std::unique_ptr<TaskRepository>& repository) override;
};

#endif //TASKMANAGER_CORE_DATAPERSISTER_TASKPERSISTER_H_
