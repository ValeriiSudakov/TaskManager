//
// Created by valeriisudakov on 29.09.20.
//

#include <gtest/gtest.h>
#include "Repository/TaskRepositoryClass.h"
#include "Persister/TaskPersister.h"
#include "Repository/RepositoriesFactory/TaskRepositoryFactory.h"

class TestTaskPersister : public ::testing::Test {
 protected:
  void SetUp() override{
    factory = std::make_unique<TaskRepositoryFactory>();
    repository = std::move(factory->Create());
    auto task = TaskRepositoryDTO::Create("name", "label", Priority::FIRST, Date::GetCurrentTime());
    auto addResult = repository->AddTask(task.value());
    repository->AddSubtask(addResult.id_.value(), task.value());
  }
  void TearDown() override{
    repository.reset();
  }
 protected:

  std::unique_ptr<RepositoriesFactory> factory;
  std::unique_ptr<TaskRepository> repository;
};

TEST_F(TestTaskPersister, shouldSave){
  std::fstream file("file.txt", std::fstream::out);
  std::unique_ptr<Persister> persister = std::make_unique<TaskPersister>(*repository, file);
  auto result = persister->Save();
  ASSERT_TRUE(result);
}

TEST_F(TestTaskPersister, shouldLoad){
  std::fstream file("file1.txt", std::fstream::out);
  std::unique_ptr<Persister> persister = std::make_unique<TaskPersister>(*repository, file);
  auto resultSave = persister->Save();
  ASSERT_TRUE(resultSave);
  persister.reset();
  std::unique_ptr<TaskRepository> repository1 = std::move(factory->Create());

  std::fstream file1("file1.txt", std::fstream::in);
  std::unique_ptr<Persister> persister1 = std::make_unique<TaskPersister>(*repository1, file1);
  auto resultLoad = persister1->Load();
  ASSERT_TRUE(resultLoad);

  auto tasksOld = repository->GetTasks();
  auto tasksNew = repository1->GetTasks();

  auto subtasksOfFisrtOld = repository->GetSubtask(tasksOld[0].GetID());
  auto subtasksOfFisrtNew = repository1->GetSubtask(tasksNew[0].GetID());


  ASSERT_EQ(subtasksOfFisrtOld.size(),subtasksOfFisrtNew.size());
  ASSERT_EQ(tasksOld.size(), 2);
  ASSERT_EQ(tasksOld[0].GetName(), tasksNew[0].GetName());
  ASSERT_EQ(tasksOld[0].GetLabel(),  tasksNew[0].GetLabel());
  ASSERT_EQ(tasksOld[0].GetPriority(), tasksNew[0].GetPriority());
  ASSERT_EQ(tasksOld[0].GetDate().Get(),  tasksNew[0].GetDate().Get());
}