//
// Created by valerii.sudakov on 8/4/2020.
//

#include <gtest/gtest.h>
#include "Memory_Model/Storage/TaskRepository.h"

class TestTaskRepository : public ::testing::Test {

};

TEST_F(TestTaskRepository, shouldGetTaskView){
  TaskRepository tr;
  ASSERT_NE(&tr.GetTaskView(), nullptr);
}
TEST_F(TestTaskRepository, shouldGetTaskStorage){
  TaskRepository tr;
  ASSERT_NE(&tr.GetTaskStorage(), nullptr);
}
