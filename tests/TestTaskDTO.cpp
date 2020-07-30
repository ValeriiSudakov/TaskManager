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
  Task task = Task::Create("task name", "label", Task::Priority::NONE, date);

  TaskDTO taskDTO(task, false,  taskIDGenerate.Generate());

  ASSERT_EQ(taskDTO.task_.GetName(), "task name");
  ASSERT_EQ(taskDTO.task_.GetLabel(), "label");
  ASSERT_EQ(taskDTO.task_.GetPriority(), Task::Priority::NONE);
  tm date1 = taskDTO.task_.GetDueDate();
  ASSERT_EQ(mktime(&date1), mktime(&date));
  ASSERT_EQ(taskDTO.taskID_.GetID(),  0);
  ASSERT_EQ(taskDTO.taskComplete_, false);

}