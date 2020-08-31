//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_CONTEXT_H_
#define TASKMANAGER_CLI_CONTEXT_H_
#include "API/TaskService.h"

struct Context {
  Context();

  std::unique_ptr<TaskService> taskService_;
  struct Buffer {
    std::string name;
    std::string label;
    Priority priority;
    Date date;
    TaskID id;
  } buffer_;
  std::vector<TaskDTO> tasks_;
};

#endif //TASKMANAGER_CLI_CONTEXT_H_
