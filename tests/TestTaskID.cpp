//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskID.h"
#include "TaskIDGenerate.h"
#include <iostream>

class TestTaskIDClass : public ::testing::Test {

};

TEST_F(TestTaskIDClass, shouldIncrement){
  TaskIDGenerate taskIDGenerate;
  TaskID taskID =  taskIDGenerate.Generate();
  auto id1 = taskIDGenerate.Generate();
  auto id2 = taskIDGenerate.Generate();
  ASSERT_NE(id1,id2);
  ASSERT_EQ(id1+1,id2);
}
