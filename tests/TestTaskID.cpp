//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskID.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <iostream>

class TestTaskIDClass : public ::testing::Test {

};

TEST_F(TestTaskIDClass, shouldIncrement){
  TaskIDGenerate taskIDGenerate;

  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());

  ASSERT_NE(id1.Get(),id2.Get());
  ASSERT_EQ(id1.Get()+1,id2.Get());
}

TEST_F(TestTaskIDClass, shouldEqual){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  ASSERT_EQ(id1, id1);
}

TEST_F(TestTaskIDClass, shouldntEqual){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());
  ASSERT_NE(id1, id2);
}

TEST_F(TestTaskIDClass, shouldBeLess){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());
  ASSERT_TRUE(id1.operator<(id2));
  ASSERT_FALSE(id2.operator<(id1));
}

TEST_F(TestTaskIDClass, shoulBeBiggest){
  TaskIDGenerate taskIDGenerate;
  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());
  ASSERT_TRUE(id2.operator>(id1));
  ASSERT_FALSE(id1.operator>(id2));
}