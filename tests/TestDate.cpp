//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "TaskService.h"
#include <iostream>
#include <stdexcept>

class TestTaskServiceClass : public ::testing::Test {

};

TEST_F(TestTaskServiceClass, CreateDate) {

  Date date = TaskService::CreateDate(11, 10, 2020, 3);

  ASSERT_EQ(date.dueDate.tm_mday, 11);
  ASSERT_EQ(date.dueDate.tm_mon, 10);
  ASSERT_EQ(date.dueDate.tm_year, 2020);
  ASSERT_EQ(date.dueDate.tm_wday, 3);

  EXPECT_THROW(TaskService::CreateDate(-11,-15,-1231,-11), std::runtime_error);
  EXPECT_THROW(TaskService::CreateDate(1252,125326,1253621,77177), std::runtime_error);

}
