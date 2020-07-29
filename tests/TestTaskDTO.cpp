//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "TaskDTO.h"
#include "Date.h"
#include <iostream>

class TestTaskDTOClass : public ::testing::Test {

};

TEST_F(TestTaskDTOClass, CreateTaskDTO){
  TaskID taskID;
  tm date = Date::GetCurrentTime();
  Task task = Task::Create("task name", "label", Task::Priority::HIGH, date);

  TaskDTO taskDTO(task, false, taskID);

  ASSERT_EQ(taskDTO.task.GetName(), "task name");
  ASSERT_EQ(taskDTO.task.GetLabel(), "label");
  ASSERT_EQ(taskDTO.task.GetPriority(), Task::Priority::HIGH);
  tm date1 = taskDTO.task.GetDueDate();
  ASSERT_EQ(mktime(&date1), mktime(&date));
  ASSERT_EQ(taskDTO.taskID.GetID(), taskID.GetID());
  ASSERT_EQ(taskDTO.taskComplete, false);

}