//
// Created by R2D2 on 29.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskDTO.h"
#include "Memory_Model/Date/Date.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <iostream>

class TestTaskDTOClass : public ::testing::Test {

};

TEST_F(TestTaskDTOClass, shouldCreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  std::optional<Task> task = Task::Create("task name", "label", Priority::NONE, date);

  TaskDTO taskDTO(task.value().GetName(), task.value().GetLabel(), task.value().GetPriority(),
                  task.value().GetDueDate(), false,  taskIDGenerate.Generate());

  ASSERT_EQ(taskDTO.GetName(), "task name");
  ASSERT_EQ(taskDTO.GetLabel(), "label");
  ASSERT_EQ(taskDTO.GetPriority(), Priority::NONE);
  Date date1 = taskDTO.GetDate();
  ASSERT_EQ(date.Get().day_number(), date1.Get().day_number());
  ASSERT_EQ(taskDTO.GetTaskId().GetID(),  0);
  ASSERT_EQ(taskDTO.IsTaskComplete(), false);

}