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
  unsigned int first = taskID.CreateID();
  unsigned int second = taskID.CreateID();
  ASSERT_EQ(first+1, second);
}
