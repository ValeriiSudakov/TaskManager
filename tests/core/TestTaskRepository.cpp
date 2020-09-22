//
// Created by valerii.sudakov on 8/4/2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Memory_Model/Storage/TaskRepositoryClass.h"

using ::testing::Return;

class TestTaskRepository : public ::testing::Test {
};

class MockStorage : public TaskStorage{
 public:
  MOCK_METHOD(std::optional<std::shared_ptr<TaskEntity>>, GetTask, (const TaskID&),(const override));
  MOCK_METHOD(std::optional<std::shared_ptr<TaskEntity>>, AddTask, (const Task&),(override));
  MOCK_METHOD(std::optional<std::shared_ptr<TaskEntity>>, AddSubtask, (const TaskID&, const Task&),(override));
  MOCK_METHOD(bool,                                       RemoveTask, (const TaskID&), (override) );
  MOCK_METHOD(bool,                                       PostponeTask, (const TaskID&, const Date&), (override));
  MOCK_METHOD(bool,                                       SaveToFile, (const std::string&), (override));
  MOCK_METHOD(bool,                                       LoadFromFile, (const std::string&), (override));
};


TEST_F(TestTaskRepository, shouldAddTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  auto task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  auto result = tr.AddTask(dto);

  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldAddSubTask) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  auto result = tr.AddSubtask(tr.GetTaskView()->GetTasksByName("task")[0].GetId(),subtaskDTO);


  ASSERT_TRUE(result.success_);
}

TEST_F(TestTaskRepository, shouldntAddSubTask) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(subTask->GetName(), subTask->GetLabel(), subTask->GetPriority(), subTask->GetDueDate());
  auto result = tr.AddSubtask(TaskID(2134515),subtaskDTO);


  ASSERT_FALSE(result.success_);
}

TEST_F(TestTaskRepository, shouldRemoveTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(subTask->GetName(), subTask->GetLabel(), subTask->GetPriority(), subTask->GetDueDate());
  tr.AddSubtask(tr.GetTaskView()->GetTasksByName("task")[0].GetId(),subtaskDTO);

  std::optional<Task> subTask1 = Task::Create("sub task1", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO1 = TaskDTO::Create(subTask1->GetName(), subTask1->GetLabel(), subTask1->GetPriority(), subTask1->GetDueDate());
  tr.AddSubtask(tr.GetTaskView()->GetTasksByName("sub task")[0].GetId(),subtaskDTO1);


  ASSERT_TRUE(tr.RemoveTask(TaskID(0)));
  ASSERT_FALSE(tr.GetTaskStorage()->GetTask(TaskID(0)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage()->GetTask(TaskID(1)).has_value());
  ASSERT_FALSE(tr.GetTaskStorage()->GetTask(TaskID(2)).has_value());
}

TEST_F(TestTaskRepository, shouldntRemoveTask){
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  ASSERT_FALSE(tr.RemoveTask(TaskID(421)));
}


TEST_F(TestTaskRepository, shouldSaveToFile){
  auto mockStorage = std::make_unique<MockStorage>();
  EXPECT_CALL(*mockStorage, SaveToFile).Times(1).WillOnce(Return(true));

  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(mockStorage));

  auto result = tr.SaveToFile("SaveFile.txt");
  ASSERT_TRUE(result);
}

TEST_F(TestTaskRepository, shouldLoadFromFile){

  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));

  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);
  auto resultSave = tr.SaveToFile("SaveFile.txt");
  ASSERT_TRUE(resultSave);

  auto resultLoad = tr.LoadFromFile("SaveFile.txt");
  ASSERT_TRUE(resultLoad);

  auto taskStorage1 = tr.GetTaskStorage()->GetTask(TaskID(0));
  auto taskView1 = tr.GetTaskView()->GetTasksByName("task");
  ASSERT_EQ(taskStorage1.value()->GetName(), taskView1[0].GetName());
  ASSERT_EQ(taskStorage1.value()->GetSubtasks().size(), 0);
}


TEST_F(TestTaskRepository, shouldntLoadFromFile) {
  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  tr.AddTask(TaskDTO::Create("a", "n", Priority::NONE, Date::GetCurrentTime()));

  auto oldTasks = tr.GetTaskView()->GetTasks().size();
  ASSERT_EQ(oldTasks, 1);

  auto result = tr.LoadFromFile("FileDoesntExist.txt");
  ASSERT_FALSE(result);

  auto newTasks = tr.GetTaskView()->GetTasks().size();
  ASSERT_EQ(newTasks, 1);
}


TEST_F(TestTaskRepository, shouldCorrectSaveLoadWhenDeleteTask) {

  TaskRepositoryClass tr(std::move(std::make_unique<TaskViewClass>()), std::move(std::make_unique<TaskStorageClass>()));
  std::optional<Task> task = Task::Create("task", "label", Priority::NONE, Date::GetCurrentTime());
  auto dto = TaskDTO::Create(task->GetName(), task->GetLabel(), task->GetPriority(), task->GetDueDate());
  tr.AddTask(dto);

  std::optional<Task> subTask = Task::Create("sub task", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO = TaskDTO::Create(subTask->GetName(), subTask->GetLabel(), subTask->GetPriority(), subTask->GetDueDate());
  tr.AddSubtask(tr.GetTaskView()->GetTasksByName("task")[0].GetId(),subtaskDTO);

  std::optional<Task> subTask1 = Task::Create("sub task1", "label", Priority::NONE, Date::GetCurrentTime());
  auto subtaskDTO1 = TaskDTO::Create(subTask1->GetName(), subTask1->GetLabel(), subTask1->GetPriority(), subTask1->GetDueDate());
  tr.AddSubtask(tr.GetTaskView()->GetTasksByName("task")[0].GetId(),subtaskDTO1);

  auto numberSubtaskOld = tr.GetTaskView()->GetTasksByName("task")[0].GetSubtasks().size();
  ASSERT_EQ(numberSubtaskOld, 2);

  auto removeResult = tr.RemoveTask(tr.GetTaskView()->GetTasksByName("sub task")[0].GetId());
  ASSERT_TRUE(removeResult);

  auto resultSave = tr.SaveToFile("SaveFile.txt");
  ASSERT_TRUE(resultSave);

  auto resultLoad = tr.LoadFromFile("SaveFile.txt");
  ASSERT_TRUE(resultLoad);

  auto numberSubtaskNew = tr.GetTaskView()->GetTasksByName("task")[0].GetSubtasks().size();
  ASSERT_EQ(numberSubtaskNew, 1);
}