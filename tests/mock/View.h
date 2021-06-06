/*!
* Copyright (c) 2021 by Cisco Systems, Inc.
* All rights reserved.
*/
//

#include "TaskView.h"
#include <gmock/gmock.h>

class MockView : public TaskView {
 public:
  MOCK_METHOD(void,                      AddTask,            (const std::weak_ptr<TaskEntity> &task), (override));
  MOCK_METHOD(bool,                      RemoveTask,         (const std::weak_ptr<TaskEntity> &task), (override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetTasks,           (),                                      (const override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetTodayTasks,      (),                                      (const override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetWeekTasks,       (),                                      (const override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetTasksByDate,     (const Date&),                           (const override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetTasksByLabel,    (const std::string&),                    (const override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetTasksByName,     (const std::string&),                    (const override));
  MOCK_METHOD(std::vector<TaskEntity>,   GetTasksByPriority, (Priority),                              (const override));
};