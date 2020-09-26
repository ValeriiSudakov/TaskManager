//
// Created by valeriisudakov on 25.09.20.
//

#include <gtest/gtest.h>
#include "Memory_Model/Storage/TaskRepositoryClass.h"
#include "DataPersister/TaskPersister.h"

class TestTaskPersister : public ::testing::Test {
 protected:
  void SetUp() override{
    repository = std::make_unique<TaskRepositoryClass>(std::make_unique<TaskViewClass>(),
                                                       std::make_unique<TaskStorageClass>());
    persister = std::make_unique<DataPersister::TaskPersister>();
    auto task = Task::Create("name", "label", Priority::FIRST, Date::GetCurrentTime());
    repository->AddTask(task.value());
  }
  void TearDown() override{
    repository.reset();
  }
 protected:
  std::unique_ptr<TaskRepository> repository;
  std::unique_ptr<DataPersister::Persister> persister;
};

TEST_F(TestTaskPersister, shouldSave){
  auto result = persister->Save("TestPersister.txt", *repository);
  ASSERT_TRUE(result);
}

TEST_F(TestTaskPersister, shouldLoad){
  auto resultSave = persister->Save("TestPersister.txt", *repository);
  ASSERT_TRUE(resultSave);

  auto resultLoad = persister->Load("TestPersister.txt", repository);
  ASSERT_TRUE(resultLoad);

  auto tasks = repository->GetTaskStorage()->GetTasks();
  ASSERT_EQ(tasks.size(), 1);
  ASSERT_EQ(tasks[0]->GetTask().GetName(), "name");
  ASSERT_EQ(tasks[0]->GetTask().GetLabel(), "label");
  ASSERT_EQ(tasks[0]->GetTask().GetPriority(), Priority::FIRST);
  ASSERT_EQ(tasks[0]->GetTask().GetDueDate().Get(), Date::GetCurrentTime());
}