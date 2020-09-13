//
// Created by valeriisudakov on 17.08.20.
//

#include <gtest/gtest.h>
#include "Memory_Model/Convertor.h"


class TestConvertor : public ::testing::Test{
 protected:
 protected:
  virtual void SetUp() {
    auto task1 = Task::Create("task1", "label1", Priority::FIRST, Date::GetCurrentTime());
    TaskEntity t1(task1.value(), TaskID(1));

    auto task2 = Task::Create("task2", "label2", Priority::SECOND, Date::GetCurrentTime());
    TaskEntity t2(task2.value(), TaskID(2));

    auto task3 = Task::Create("task3", "label3", Priority::THIRD, Date::GetCurrentTime());
    TaskEntity t3(task3.value(), TaskID(3));

    auto task4 = Task::Create("task4", "label4", Priority::NONE, Date::GetCurrentTime());
    TaskEntity t4(task4.value(), TaskID(4));

    tasksVector.push_back(t2);
    tasksVector.push_back(t1);
    tasksVector.push_back(t3);
    tasksVector.push_back(t4);
  }
  std::vector<TaskEntity> tasksVector;


};

TEST_F(TestConvertor, shouldConvertToDTO){
  auto tasksDTOVector = convertor::toTaskDTO::notSortedVector(tasksVector);

  ASSERT_FALSE(tasksDTOVector.empty());
  ASSERT_EQ(tasksVector[0].GetTask().GetName(), tasksDTOVector[0].GetName());
  ASSERT_EQ(tasksVector[1].GetTask().GetPriority(), tasksDTOVector[1].GetPriority());
  ASSERT_EQ(tasksVector[2].GetTask().GetLabel(), tasksDTOVector[2].GetLabel());
}

TEST_F(TestConvertor, shouldConvertToSortedDTO){
  auto tasksDTOVector = convertor::toTaskDTO::sortedVectorByPriority(tasksVector);

  ASSERT_FALSE(tasksDTOVector.empty());
  ASSERT_EQ(tasksDTOVector[0].GetPriority(), Priority::FIRST);
  ASSERT_EQ(tasksDTOVector[1].GetPriority(), Priority::SECOND);
  ASSERT_EQ(tasksDTOVector[2].GetPriority(), Priority::THIRD);
  ASSERT_EQ(tasksDTOVector[3].GetPriority(), Priority::NONE);

}