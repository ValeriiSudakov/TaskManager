//
// Created by valeriisudakov on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskID.h"
#include "TaskIDGenerate.h"
#include <iostream>

class TestTaskID : public ::testing::Test {

};

TEST_F(TestTaskID, shouldIncrement){
  TaskIDGenerate taskIDGenerate;

  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());

  ASSERT_NE(id1,id2);
}

TEST_F(TestTaskID, shouldEqual){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  ASSERT_EQ(id1, id1);
}

TEST_F(TestTaskID, shouldntEqual){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());
  ASSERT_NE(id1, id2);
}

TEST_F(TestTaskID, shouldBeLess){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());
  ASSERT_TRUE(operator<(id1, id2));
  ASSERT_FALSE(operator<(id2, id1));
}

TEST_F(TestTaskID, shoulBeBiggest){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());
  ASSERT_TRUE(operator>(id2, id1));
  ASSERT_FALSE(operator>(id1, id2));
}