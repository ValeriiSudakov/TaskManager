//
// Created by valeriisudakov on 29.07.2020.
//

#include <gtest/gtest.h>
#include <iostream>
#include "TaskServiceDTO.h"
#include "Date.h"
#include "TaskIDGenerate.h"
#include "TaskServiceDTOUtils.h"
#include "Task.h"

class TestTaskServiceDTO : public ::testing::Test {

};

TEST_F(TestTaskServiceDTO, shouldCreateTaskDTO){
  TaskIDGenerate taskIDGenerate;
  Date date = Date::GetCurrentTime();
  TaskID id = taskIDGenerate.Generate();
  std::optional<Task> task = Task::Create("task name", "label", Priority::NONE, date);

  auto taskDTO = TaskServiceDTO::Create(task.value().GetName(), task.value().GetLabel(), task.value().GetPriority(),
                                                task.value().GetDueDate(), false, id);
  ASSERT_TRUE(taskDTO.has_value());


  ASSERT_EQ(taskDTO.value().GetName(), "task name");
  ASSERT_EQ(taskDTO.value().GetLabel(), "label");
  ASSERT_EQ(taskDTO.value().GetPriority(), Priority::NONE);
  Date date1 = taskDTO.value().GetDate();
  ASSERT_EQ(date.Get().day_number(), date1.Get().day_number());
  ASSERT_EQ(taskDTO.value().GetTaskId(),  id);
  ASSERT_EQ(taskDTO.value().IsTaskComplete(), false);

}

TEST_F(TestTaskServiceDTO, shouldConvertToString){
  auto dto = TaskServiceDTO::Create("name", "label", Priority::FIRST,
                                              Date::GetCurrentTime(), false, TaskID(0));

  std::string dtoStrNotCompleted = "Task name: " + dto.value().GetName() + "\nTask label: " + dto.value().GetLabel() +
      "\nTask priority: " + task_service_dto_utils::PriorityToString(dto.value().GetPriority())
      + (dto.value().IsTaskComplete() ? "\nCompleted" : "\nNot completed") + "\nDate: " + dto.value().GetDate().ToString();

  ASSERT_EQ(dtoStrNotCompleted, dto.value().ToString());

  auto dto1 = TaskServiceDTO::Create("asdas", "ladasdasdbel", Priority::SECOND,
                                    Date::GetCurrentTime(), true, TaskID(0));

  std::string dtoStrCompleted = "Task name: " + dto1.value().GetName() + "\nTask label: " + dto1.value().GetLabel() +
      "\nTask priority: " + task_service_dto_utils::PriorityToString(dto1.value().GetPriority())
      + (dto1.value().IsTaskComplete() ? "\nCompleted" : "\nNot completed") + "\nDate: " + dto1.value().GetDate().ToString();

  ASSERT_EQ(dtoStrCompleted, dto1.value().ToString());
}
