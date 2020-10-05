//
// Created by valeriisudakov on 03.10.20.
//

#include <gtest/gtest.h>
#include "Memory_Model/Storage/TaskRepositoryController.h"
#include "API/TaskServiceUtils.h"

class TestTaskRepositoryController : public ::testing::Test {
 protected:
  void SetUp() override{
    repository = std::make_unique<TaskRepositoryController>(TaskServiceUtils::GetRepositoryFactory());
  }
 protected:
  std::unique_ptr<TaskRepositoryController> repository;
};

TEST_F(TestTaskRepositoryController, shouldSaveAndLoad){
  auto testTask = TaskRepositoryDTO::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testTask.has_value());
  auto addTaskResult = repository->Get()->AddTask(testTask.value());
  ASSERT_TRUE(addTaskResult.success_);

  auto testSubtask = TaskRepositoryDTO::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  ASSERT_TRUE(testSubtask.has_value());
  auto addSubtaskResult = repository->Get()->AddSubtask(addTaskResult.id_.value(), testSubtask.value());
  ASSERT_TRUE(addSubtaskResult.success_);

  ASSERT_TRUE(repository->Save());
  ASSERT_TRUE(repository->Load());

  auto tasks = repository->Get()->GetTasks();
  ASSERT_EQ(tasks.size(), 2);
  ASSERT_EQ(tasks[0].GetName(), "task");
  ASSERT_EQ(tasks[0].GetLabel(), "label");
  ASSERT_EQ(tasks[0].GetPriority(), Priority::NONE);
  ASSERT_EQ(tasks[0].GetDate().Get().day_number(), Date::GetCurrentTime().day_number());

  auto subtaskFirst = repository->Get()->GetSubtask(tasks[0].GetID());
  ASSERT_EQ(subtaskFirst.size(), 1);
}
