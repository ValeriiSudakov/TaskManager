//
// Created by valeriisudakov on 18.08.20.
//

#ifndef TASKMANAGER_CLI_CONTEXT_H_
#define TASKMANAGER_CLI_CONTEXT_H_
#include "TaskService.h"

struct Context {
  Context(TaskService& taskService) : taskService_(taskService){}
  ~Context() = default;

  TaskService& taskService_;
  struct Buffer {
    std::string name;
    std::string label;
    Priority priority;
    Date date;
    TaskID id;
    std::string fileName;
  } buffer_;
  std::vector<TaskServiceDTO> tasks_;
};

#endif //TASKMANAGER_CLI_CONTEXT_H_
