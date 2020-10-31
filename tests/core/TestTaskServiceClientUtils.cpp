////
//// Created by valeriisudakov on 30.10.20.
////

#include <gtest/gtest.h>
#include "mock/TransportServiceStub.h"
#include "API/Service/TaskServiceClient.h"
#include "API/Utils/TaskServiceClientUtils.h"
#include "Persister/Utils/TaskPersisterUtils.h"

class TestTaskServiceClientUtils : public ::testing::Test {

};

TEST_F(TestTaskServiceClientUtils, shouldFillTransportTaskFromDTO){
  auto dto = TaskServiceDTO::Create("name", "label", Priority::FIRST, Date::GetCurrentTime());
  auto task = std::make_unique<transport::Task>();
  task_service_client_utils::FillTransportTaskFromDTO(dto.value(), task.get());
  ASSERT_EQ(task->name(), dto.value().GetName());
  ASSERT_EQ(task->label(), dto.value().GetLabel());
  ASSERT_EQ(persister_utils::SerializedPriorityToPriority(task->priority()), dto.value().GetPriority());
  ASSERT_EQ(task->date().value(), dto.value().GetDate().Get().day_number());
}

TEST_F(TestTaskServiceClientUtils, shouldConvertAddTaskErrorFromTransportError){
  ASSERT_EQ(task_service_client_utils::FromTransportError(transport::Error::NOT_FOUND_PARENT_TASK),
                                                          AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK);
  ASSERT_EQ(task_service_client_utils::FromTransportError(transport::Error::TASK_IS_DAMAGED),
                                                          AddTaskResult::ErrorType::TASK_IS_DAMAGED);
  ASSERT_EQ(task_service_client_utils::FromTransportError(transport::Error::NOT_ENOUGH_FREE_MEMORY),
                                                          AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY);
}


TEST_F(TestTaskServiceClientUtils, shouldConvertTaskServiceDTOfromTransportTask){
  auto task = std::make_unique<transport::Task>();
  ASSERT_FALSE(task_service_client_utils::FromTransportTask(*task).has_value());

  task->set_name("name");
  task->set_label("label");
  task->set_priority(proto::FIRST);
  task->mutable_date()->set_value(Date::GetCurrentTime().day_number());

  auto dto = task_service_client_utils::FromTransportTask(*task);
  ASSERT_TRUE(dto.has_value());

  ASSERT_EQ(task->name(), dto.value().GetName());
  ASSERT_EQ(task->label(), dto.value().GetLabel());
  ASSERT_EQ(persister_utils::SerializedPriorityToPriority(task->priority()), dto.value().GetPriority());
  ASSERT_EQ(task->date().value(), dto.value().GetDate().Get().day_number());
}

