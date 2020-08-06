//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "Memory_Model/Task/TaskID.h"
#include "Memory_Model/Task/TaskIDGenerate.h"
#include <iostream>

class TestTaskIDClass : public ::testing::Test {

};

TEST_F(TestTaskIDClass, shouldIncrement){
  TaskIDGenerate taskIDGenerate;

  TaskID id1(taskIDGenerate.Generate());
  TaskID id2(taskIDGenerate.Generate());

  ASSERT_NE(id1.GetID(),id2.GetID());
  ASSERT_EQ(id1.GetID()+1,id2.GetID());
}
