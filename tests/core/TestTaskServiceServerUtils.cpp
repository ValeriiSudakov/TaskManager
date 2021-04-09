//
// Created by valeriisudakov on 28.10.20.
//

#include <gtest/gtest.h>
#include "TaskServiceServerUtils.h"
#include "TaskPersisterUtils.h"
#include "utils.h"
class TestTaskServiceServerUtils : public ::testing::Test {

};

TEST_F(TestTaskServiceServerUtils, shouldConvertToTransportTask){
  auto dto = TaskRepositoryDTO::Create("name", "label", Priority::FIRST, Date::GetCurrentTime()).value();
  auto result = task_service_server_utils::ToTransport(dto);
  ASSERT_EQ(dto.GetName(), result.name());
  ASSERT_EQ(dto.GetLabel(), result.label());
  ASSERT_EQ(dto.GetPriority(), SerializedPriorityToPriority(result.priority()));
  ASSERT_EQ(dto.GetDate().Get().day_number(), result.date().value());
}


TEST_F(TestTaskServiceServerUtils, shouldConvertToTransportResult){
  AddTaskResult resultSuccess = AddTaskResult::Success(TaskID(0));
  AddTaskResult resultFail = AddTaskResult::Failed(AddTaskResult::ErrorType::TASK_IS_DAMAGED);

  auto transportSuccess = task_service_server_utils::ToTransport(resultSuccess);
  ASSERT_EQ(resultSuccess.success_, transportSuccess.success());
  ASSERT_EQ(resultSuccess.id_.value().Get(), transportSuccess.id().value());

  auto transportFail = task_service_server_utils::ToTransport(resultFail);
  ASSERT_EQ(resultFail.success_, transportFail.success());
  ASSERT_EQ(task_service_server_utils::ToTransport(resultFail.error_.value()), transportFail.error());
}

TEST_F(TestTaskServiceServerUtils, shouldConvertToTransportError){
  ASSERT_EQ(task_service_server_utils::ToTransport(AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK), transport::Error::NOT_FOUND_PARENT_TASK);
  ASSERT_EQ(task_service_server_utils::ToTransport(AddTaskResult::ErrorType::TASK_IS_DAMAGED) ,transport::Error::TASK_IS_DAMAGED);
  ASSERT_EQ(task_service_server_utils::ToTransport(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY), transport::Error::NOT_ENOUGH_FREE_MEMORY);
}

TEST_F(TestTaskServiceServerUtils, shouldConvertToTaskRepositoryDTO){
  transport::Task task;
  task.set_name("name");
  task.set_label("label");
  task.set_priority(proto::NONE);
  task.mutable_date()->set_value(Date::GetCurrentTime().day_number());
  auto dto = task_service_server_utils::ToTaskRepositoryDTO(task);

  ASSERT_EQ(dto.value().GetName(), task.name());
  ASSERT_EQ(dto.value().GetLabel(), task.label());
  ASSERT_EQ(dto.value().GetPriority(), SerializedPriorityToPriority(task.priority()));
  ASSERT_EQ(dto.value().GetDate().Get().day_number(), task.date().value());
}

TEST_F(TestTaskServiceServerUtils, shouldSortTasksDTO){
  std::vector<TaskRepositoryDTO> tasks;
  tasks.push_back(TaskRepositoryDTO::Create("name", "label", Priority::NONE, Date::GetCurrentTime()).value());
  tasks.push_back(TaskRepositoryDTO::Create("name", "label", Priority::FIRST, Date::GetCurrentTime()).value());

  ASSERT_EQ(tasks[0].GetPriority(), Priority::NONE);
  ASSERT_EQ(tasks[1].GetPriority(), Priority::FIRST);
  task_service_server_utils::SortTasks(tasks);
  ASSERT_EQ(tasks[1].GetPriority(), Priority::NONE);
  ASSERT_EQ(tasks[0].GetPriority(), Priority::FIRST);
}

TEST_F(TestTaskServiceServerUtils, shouldFillTransportTask){
  transport::Task source;
  source.set_name("name");
  source.set_label("label");
  source.set_priority(proto::NONE);
  source.mutable_date()->set_value(Date::GetCurrentTime().day_number());
  auto result = std::make_unique<transport::Task>();
  task_service_server_utils::FillTransportTask(source, result.get());

  ASSERT_EQ(source.name(),result->name());
  ASSERT_EQ(source.label(),result->label());
  ASSERT_EQ(source.priority(), result->priority());
  ASSERT_EQ(source.date().value(),result->date().value());
}
