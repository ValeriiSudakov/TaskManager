//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "TaskDTO.h"
#include "Date.h"
#include "TaskIDGenerate.h"
#include <iostream>

class TestTaskDTOClass : public ::testing::Test {

};

TEST_F(TestTaskDTOClass, CreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  tm date = Date::GetCurrentTime();
  Task task = Task::Create("task name", "label", Task::Priority::HIGH, date);

  TaskDTO taskDTO(task, false,  taskIDGenerate.Generate());

  ASSERT_EQ(taskDTO.task.GetName(), "task name");
  ASSERT_EQ(taskDTO.task.GetLabel(), "label");
  ASSERT_EQ(taskDTO.task.GetPriority(), Task::Priority::HIGH);
  tm date1 = taskDTO.task.GetDueDate();
  ASSERT_EQ(mktime(&date1), mktime(&date));
  ASSERT_EQ(taskDTO.taskID.GetID(),  0);
  ASSERT_EQ(taskDTO.taskComplete, false);

}