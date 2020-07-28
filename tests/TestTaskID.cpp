//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskID.h"
#include <iostream>

class TestTaskIDClass : public ::testing::Test {

};

TEST_F(TestTaskIDClass, shouldIncrement){
  TaskID taskID;
  auto id1 = taskID.GenerateID();
  auto id2 = taskID.GenerateID();
  ASSERT_NE(id1,id2);
  ASSERT_EQ(id1+1,id2);
}
