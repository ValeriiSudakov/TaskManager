//
// Created by valeriisudakov on 29.07.2020.
//

#include "gtest/gtest.h"
#include "TaskRepositoryUtils.h"

class TestTaskRepositoryUtils : public ::testing::Test {

};

TEST_F(TestTaskRepositoryUtils, shouldMakeDTOfromEntity){
  auto task = Task::Create("name", "label", Priority::NONE, Date::GetCurrentTime());
  auto entity = TaskEntity(task.value(), TaskID());
  auto dto = task_repository_utils::DTOFromEntity(entity);
  ASSERT_EQ(dto.GetName(), entity.GetName());
  ASSERT_EQ(dto.GetLabel(), entity.GetLabel());
  ASSERT_EQ(dto.GetPriority(), entity.GetPriority());
  ASSERT_EQ(dto.GetDate().Get().day_number(), entity.GetDueDate().Get().day_number());
}

TEST_F(TestTaskRepositoryUtils, shouldMakeEntityFromDTO){
  TaskIDGenerate generate;
  auto dto = TaskRepositoryDTO::Create("root", "label", Priority::NONE, Date::GetCurrentTime());
  auto rootEntity = task_repository_utils::NewEntityFromDTO(dto.value(), generate, std::nullopt);
  ASSERT_EQ(dto.value().GetName(), rootEntity.value().GetName());
  ASSERT_EQ(dto.value().GetLabel(), rootEntity.value().GetLabel());
  ASSERT_EQ(dto.value().GetPriority(), rootEntity.value().GetPriority());
  ASSERT_EQ(dto.value().GetDate().Get().day_number(), rootEntity.value().GetDueDate().Get().day_number());


  auto dto1 = TaskRepositoryDTO::Create("root", "label", Priority::NONE, Date::GetCurrentTime());
  auto subEntity = task_repository_utils::NewEntityFromDTO(dto.value(), generate, rootEntity.value().GetId());
  ASSERT_EQ(dto1.value().GetName(), subEntity.value().GetName());
  ASSERT_EQ(dto1.value().GetLabel(), subEntity.value().GetLabel());
  ASSERT_EQ(dto1.value().GetPriority(), subEntity.value().GetPriority());
  ASSERT_EQ(dto1.value().GetDate().Get().day_number(), subEntity.value().GetDueDate().Get().day_number());
  ASSERT_EQ(subEntity.value().GetParentId(), rootEntity.value().GetId());
}


TEST_F(TestTaskRepositoryUtils, shouldSortByPriority) {
  std::vector<TaskRepositoryDTO> dto;
  auto task = Task::Create("1", "label", Priority::NONE, Date::GetCurrentTime());
  auto entity = TaskEntity(task.value(), TaskID());
  dto.push_back(task_repository_utils::DTOFromEntity(entity));

  auto task1 = Task::Create("2", "label", Priority::FIRST, Date::GetCurrentTime());
  auto entity1 = TaskEntity(task1.value(), TaskID());
  auto tempDTO1 = task_repository_utils::DTOFromEntity(entity1);
  dto.push_back(tempDTO1);

  ASSERT_EQ(dto[0].GetPriority(), Priority::NONE);
  ASSERT_EQ(dto[1].GetPriority(), Priority::FIRST);

  task_repository_utils::SortByPriority(dto);

  ASSERT_EQ(dto[0].GetPriority(), Priority::FIRST);
  ASSERT_EQ(dto[1].GetPriority(), Priority::NONE);
}
