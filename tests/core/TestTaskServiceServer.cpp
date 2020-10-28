//
// Created by valeriisudakov on 27.10.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "API/Service/TaskServiceServer.h"
#include <iostream>
#include "Repository/RepositoriesFactory/TaskRepositoryFactory.h"
#include "Repository/RepositoryController/TaskRepositoryController.h"
#include "API/Service/TaskServiceServer.h"
#include "Persister/Utils/TaskPersisterUtils.h"
#include "API/Utils/TaskServiceServerUtils.h"

class TestTaskServiceServer : public ::testing::Test {
 protected:
  virtual void SetUp() {
    auto factory = std::make_unique<TaskRepositoryFactory>();
    auto controller = std::make_unique<TaskRepositoryController>(std::move(factory));
    ts = std::make_unique<TaskServiceServer>(std::move(controller));

    auto response = std::make_unique<::response::AddTask>();
    auto request = std::make_unique<::requests::AddTask>();
    request->mutable_taskdata()->set_name("name");
    request->mutable_taskdata()->set_label("label");
    request->mutable_taskdata()->set_priority(proto::NONE);
    request->mutable_taskdata()->mutable_date()->set_value(Date::GetCurrentTime().day_number());
    auto result = ts->AddTask(nullptr, request.get(), response.get());
  }
  std::unique_ptr<transport::TaskService::Service> ts;
};

TEST_F(TestTaskServiceServer, shouldAddTask) {
  auto response = std::make_unique<::response::AddTask>();
  auto request = std::make_unique<::requests::AddTask>();
  request->mutable_taskdata()->set_name("name");
  request->mutable_taskdata()->set_label("label");
  request->mutable_taskdata()->set_priority(proto::NONE);
  request->mutable_taskdata()->mutable_date()->set_value(Date::GetCurrentTime().day_number());
  auto result = ts->AddTask(nullptr, request.get(), response.get());
  ASSERT_TRUE(response->result().success());
}

TEST_F(TestTaskServiceServer, shouldCreateTask) {
  auto response1 = std::make_unique<::response::GetTasksByName>();
  auto request1 = std::make_unique<::requests::GetTasksByName>();
  request1->set_name("name");
  ts->GetTasksByName(nullptr, request1.get(), response1.get());
  ASSERT_EQ(response1->tasks().size(), 1);
}


TEST_F(TestTaskServiceServer, shouldCreateSubTask) {
  auto response1 = std::make_unique<::response::AddSubtask>();
  auto request1 = std::make_unique<::requests::AddSubtask>();
  request1->mutable_subtaskdata()->set_name("subtask");
  request1->mutable_subtaskdata()->set_label("label");
  request1->mutable_subtaskdata()->set_priority(proto::NONE);
  request1->mutable_subtaskdata()->mutable_date()->set_value(Date::GetCurrentTime().day_number());
  request1->mutable_rootid()->set_value(0);
  auto result1 = ts->AddSubtask(nullptr, request1.get(), response1.get());
  ASSERT_TRUE(response1->result().success());
}

TEST_F(TestTaskServiceServer, shouldntCreateSubTaskWithIncorrectID) {
  auto response = std::make_unique<::response::AddSubtask>();
  auto request = std::make_unique<::requests::AddSubtask>();
  request->mutable_subtaskdata()->set_name("subtask");
  request->mutable_subtaskdata()->set_label("label");
  request->mutable_subtaskdata()->set_priority(proto::NONE);
  request->mutable_subtaskdata()->mutable_date()->set_value(Date::GetCurrentTime().day_number());
  request->mutable_rootid()->set_value(1423123);
  auto result1 = ts->AddSubtask(nullptr, request.get(), response.get());
  ASSERT_FALSE(response->result().success());
}

TEST_F(TestTaskServiceServer, shouldPostpone){
  auto response1 = std::make_unique<::response::PostponeTask>();
  auto request1 = std::make_unique<::requests::PostponeTask>();
  proto::Date date;
  date.set_value(Date::GetCurrentTime().day_number() + 1);
  request1->mutable_date()->set_value(date.value());
  ts->PostponeTask(nullptr, request1.get(), response1.get());
  ASSERT_TRUE(response1->success());

  auto response2 = std::make_unique<::response::GetTask>();
  auto request2 = std::make_unique<::requests::GetTask>();
  request2->mutable_id()->set_value(0);
  ts->GetTask(nullptr, request2.get(), response2.get());
  ASSERT_EQ(date.value(), response2->task().date().value());
}

TEST_F(TestTaskServiceServer, shouldGetByID) {
  auto response2 = std::make_unique<::response::GetTask>();
  auto request2 = std::make_unique<::requests::GetTask>();
  request2->mutable_id()->set_value(0);
  ts->GetTask(nullptr, request2.get(), response2.get());
  ASSERT_EQ("name", response2->task().name());
}

TEST_F(TestTaskServiceServer, shouldGetSortedTasks) {
  auto response2 = std::make_unique<::response::GetTasks>();
  auto request2 = std::make_unique<::requests::GetTasks>();
  request2->set_sortbypriority(true);
  ts->GetTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ("name", response2->tasks().Get(0).name());
}

TEST_F(TestTaskServiceServer, shouldntGetByID) {
  auto response = std::make_unique<::response::GetTask>();
  auto request = std::make_unique<::requests::GetTask>();
  request->mutable_id()->set_value(213);
  ts->GetTask(nullptr, request.get(), response.get());
  ASSERT_EQ(response->task().name(), "");
}

TEST_F(TestTaskServiceServer, shouldFoundTaskByName) {
  auto response2 = std::make_unique<::response::GetTasksByName>();
  auto request2 = std::make_unique<::requests::GetTasksByName>();
  request2->set_name("name");
  ts->GetTasksByName(nullptr, request2.get(), response2.get());
  ASSERT_EQ("name", response2->tasks().Get(0).name());
}

TEST_F(TestTaskServiceServer, shouldFoundTaskByNameAndPriority) {
  auto response2 = std::make_unique<::response::GetTasksByPriority>();
  auto request2 = std::make_unique<::requests::GetTasksByPriority>();
  request2->set_priority(proto::NONE);
  ts->GetTasksByPriority(nullptr, request2.get(), response2.get());
  ASSERT_EQ("name", response2->tasks().Get(0).name());
}

TEST_F(TestTaskServiceServer, shouldNotFoundTaskByName) {
  auto response2 = std::make_unique<::response::GetTasksByName>();
  auto request2 = std::make_unique<::requests::GetTasksByName>();
  request2->set_name("asdasdasdasdasdasdas");
  ts->GetTasksByName(nullptr, request2.get(), response2.get());
  ASSERT_EQ( response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldFoundTaskByLabel) {
  auto response2 = std::make_unique<::response::GetTasksByLabel>();
  auto request2 = std::make_unique<::requests::GetTasksByLabel>();
  request2->set_label("label");
  ts->GetTasksByLabel(nullptr, request2.get(), response2.get());
  ASSERT_EQ("label", response2->tasks().Get(0).label());
}

TEST_F(TestTaskServiceServer, shouldFoundTaskByLabelAndPriority) {
  auto response2 = std::make_unique<::response::GetTasksByLabel>();
  auto request2 = std::make_unique<::requests::GetTasksByLabel>();
  request2->set_label("label");
  request2->set_sortbypriority(true);
  ts->GetTasksByLabel(nullptr, request2.get(), response2.get());
  ASSERT_EQ("label", response2->tasks().Get(0).label());
}

TEST_F(TestTaskServiceServer, shouldNotFoundTaskByLabel) {
  auto response2 = std::make_unique<::response::GetTasksByLabel>();
  auto request2 = std::make_unique<::requests::GetTasksByLabel>();
  request2->set_label("nasdfasdfasdfasdme");
  ts->GetTasksByLabel(nullptr, request2.get(), response2.get());
  ASSERT_EQ( response2->tasks().size(), 0);
}
//
TEST_F(TestTaskServiceServer, shouldFoundTasks) {
  auto response2 = std::make_unique<::response::GetTasks>();
  auto request2 = std::make_unique<::requests::GetTasks>();
  ts->GetTasks(nullptr, request2.get(), response2.get());
  ASSERT_NE(response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldFoundTasksByPriority) {
  auto response2 = std::make_unique<::response::GetTasks>();
  auto request2 = std::make_unique<::requests::GetTasks>();
  request2->set_sortbypriority(true);
  ts->GetTasks(nullptr, request2.get(), response2.get());
  ASSERT_NE(response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldNotFoundTasks) {
  std::unique_ptr<transport::TaskService::Service> ts1;
  auto factory = std::make_unique<TaskRepositoryFactory>();
  auto controller = std::make_unique<TaskRepositoryController>(std::move(factory));
  ts1 = std::make_unique<TaskServiceServer>(std::move(controller));

  auto response2 = std::make_unique<::response::GetTasks>();
  auto request2 = std::make_unique<::requests::GetTasks>();
  ts1->GetTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldFoundTodayTasks) {
  auto response2 = std::make_unique<::response::GetTodayTasks>();
  auto request2 = std::make_unique<::requests::GetTodayTasks>();
  ts->GetTodayTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 1);
  ASSERT_EQ(response2->tasks().Get(0).name(), "name");
}

TEST_F(TestTaskServiceServer, shouldFoundTodayTasksByPriority) {
  auto response2 = std::make_unique<::response::GetTodayTasks>();
  auto request2 = std::make_unique<::requests::GetTodayTasks>();
  request2->set_sortbypriority(true);
  ts->GetTodayTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 1);
  ASSERT_EQ(response2->tasks().Get(0).name(), "name");
}

TEST_F(TestTaskServiceServer, shouldNotFoundTodayTasks) {
  std::unique_ptr<transport::TaskService::Service> ts1;
  auto factory = std::make_unique<TaskRepositoryFactory>();
  auto controller = std::make_unique<TaskRepositoryController>(std::move(factory));
  ts1 = std::make_unique<TaskServiceServer>(std::move(controller));

  auto response2 = std::make_unique<::response::GetTodayTasks>();
  auto request2 = std::make_unique<::requests::GetTodayTasks>();
  ts1->GetTodayTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldFoundWeekTasks) {
  auto response2 = std::make_unique<::response::GetWeekTasks>();
  auto request2 = std::make_unique<::requests::GetWeekTasks>();
  ts->GetWeekTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 1);
  ASSERT_EQ(response2->tasks().Get(0).name(), "name");
}

TEST_F(TestTaskServiceServer, shouldFoundWeekTasksByPriority) {
  auto response2 = std::make_unique<::response::GetWeekTasks>();
  auto request2 = std::make_unique<::requests::GetWeekTasks>();
  request2->set_sortbypriority(true);
  ts->GetWeekTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 1);
  ASSERT_EQ(response2->tasks().Get(0).name(), "name");
}

TEST_F(TestTaskServiceServer, shouldNotFoundWeekTasks) {
  std::unique_ptr<transport::TaskService::Service> ts1;
  auto factory = std::make_unique<TaskRepositoryFactory>();
  auto controller = std::make_unique<TaskRepositoryController>(std::move(factory));
  ts1 = std::make_unique<TaskServiceServer>(std::move(controller));

  auto response2 = std::make_unique<::response::GetWeekTasks>();
  auto request2 = std::make_unique<::requests::GetWeekTasks>();
  ts1->GetWeekTasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldFoundTasksPriority) {
  auto response2 = std::make_unique<::response::GetTasksByPriority>();
  auto request2 = std::make_unique<::requests::GetTasksByPriority>();
  request2->set_priority(proto::NONE);
  ts->GetTasksByPriority(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 1);
  ASSERT_EQ(response2->tasks().Get(0).priority(), proto::NONE);
}

TEST_F(TestTaskServiceServer, shouldNotFoundTasksPriority) {
  std::unique_ptr<transport::TaskService::Service> ts1;
  auto factory = std::make_unique<TaskRepositoryFactory>();
  auto controller = std::make_unique<TaskRepositoryController>(std::move(factory));
  ts1 = std::make_unique<TaskServiceServer>(std::move(controller));

  auto response2 = std::make_unique<::response::GetTasksByPriority>();
  auto request2 = std::make_unique<::requests::GetTasksByPriority>();
  ts1->GetTasksByPriority(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 0);
}

TEST_F(TestTaskServiceServer, shouldRemoveTask){
  auto response = std::make_unique<::response::RemoveTask>();
  auto request = std::make_unique<::requests::RemoveTask>();
  request->mutable_id()->set_value(0);
  ts->RemoveTask(nullptr, request.get(), response.get());
  ASSERT_TRUE(response->success());
}

TEST_F(TestTaskServiceServer, shouldntRemoveTask){
  auto response = std::make_unique<::response::RemoveTask>();
  auto request = std::make_unique<::requests::RemoveTask>();
  request->mutable_id()->set_value(123123123120);
  ts->RemoveTask(nullptr, request.get(), response.get());
  ASSERT_FALSE(response->success());
}

TEST_F(TestTaskServiceServer, shouldGetSubtasks){
  auto response2 = std::make_unique<::response::GetSubtasks>();
  auto request2 = std::make_unique<::requests::GetSubtasks>();
  request2->mutable_id()->set_value(0);
  ts->GetSubtasks(nullptr, request2.get(), response2.get());
  ASSERT_EQ(response2->tasks().size(), 0);

  auto response1 = std::make_unique<::response::AddSubtask>();
  auto request1 = std::make_unique<::requests::AddSubtask>();
  request1->mutable_subtaskdata()->set_name("subtask");
  request1->mutable_subtaskdata()->set_label("label");
  request1->mutable_subtaskdata()->set_priority(proto::NONE);
  request1->mutable_subtaskdata()->mutable_date()->set_value(Date::GetCurrentTime().day_number());
  request1->mutable_rootid()->set_value(0);
  auto result1 = ts->AddSubtask(nullptr, request1.get(), response1.get());

  auto response3 = std::make_unique<::response::GetSubtasks>();
  auto request3 = std::make_unique<::requests::GetSubtasks>();
  request3->mutable_id()->set_value(0);
  ts->GetSubtasks(nullptr, request3.get(), response3.get());
  ASSERT_EQ(response3->tasks().size(), 1);
}

TEST_F(TestTaskServiceServer, shouldSetComplete) {
  auto response2 = std::make_unique<::response::GetTask>();
  auto request2 = std::make_unique<::requests::GetTask>();
  request2->mutable_id()->set_value(0);
  ts->GetTask(nullptr, request2.get(), response2.get());
  ASSERT_FALSE(response2->task().complete());

  auto response1 = std::make_unique<::response::SetComplete>();
  auto request1 = std::make_unique<::requests::SetComplete>();
  request1->mutable_id()->set_value(0);
  ts->SetComplete(nullptr, request1.get(), response1.get());
  ASSERT_TRUE(response1->success());

  auto response3 = std::make_unique<::response::GetTask>();
  auto request3 = std::make_unique<::requests::GetTask>();
  request3->mutable_id()->set_value(0);
  ts->GetTask(nullptr, request3.get(), response3.get());
  ASSERT_TRUE(response3->task().complete());
}

TEST_F(TestTaskServiceServer, shouldSave){
  auto response1 = std::make_unique<::response::Save>();
  auto request1 = std::make_unique<::requests::Save>();
  request1->set_filename("savefile");
  ts->Save(nullptr, request1.get(), response1.get());
  ASSERT_TRUE(response1->success());
}

TEST_F(TestTaskServiceServer, shouldLoad){
  auto response1 = std::make_unique<::response::Load>();
  auto request1 = std::make_unique<::requests::Load>();
  request1->set_filename("savefile");
  ts->Load(nullptr, request1.get(), response1.get());
  ASSERT_TRUE(response1->success());
}
