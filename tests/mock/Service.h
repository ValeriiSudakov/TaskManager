//
// Created by valeriisudakov on 05.10.20.
//

#ifndef TASKMANAGER_TESTS_MOCK_SERVICE_H_
#define TASKMANAGER_TESTS_MOCK_SERVICE_H_
#include "API/TaskService.h"
#include <gmock/gmock.h>

class MockService : public TaskService{
 public:
  MOCK_METHOD(AddTaskResult,                 AddTask,            (const TaskServiceDTO&), (override));
  MOCK_METHOD(AddTaskResult,                 AddSubtask,         (const TaskID&, const TaskServiceDTO&), (override));
  MOCK_METHOD(bool,                          RemoveTask,         (const TaskID&), (override));
  MOCK_METHOD(bool,                          PostponeTask,       (const TaskID&, const Date&), (override));
  MOCK_METHOD(bool,                          SetTaskComplete,    (const TaskID&), (override));
  MOCK_METHOD(bool,                          Save, (), (override));
  MOCK_METHOD(bool,                          Load, (), (override));
  MOCK_METHOD(std::optional<TaskServiceDTO>, GetTask, (const TaskID&), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetSubtask, (const TaskID&), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasks, (bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTodayTasks, (bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetWeekTasks, (bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasksByName, (const std::string&, bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasksByLabel, (const std::string&, bool), (const override));
  MOCK_METHOD(std::vector<TaskServiceDTO>,   GetTasksByPriority, (const Priority&), (const override));
};
#endif //TASKMANAGER_TESTS_MOCK_SERVICE_H_
