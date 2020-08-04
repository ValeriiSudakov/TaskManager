//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskService.h"
#include <iostream>
#include <stdexcept>

class TestDateNamespaceClass : public ::testing::Test {

};

TEST_F(TestDateNamespaceClass, CreateDate) {

  tm date = Date::CreateDate(11, 10, 2020, 3);

  ASSERT_EQ(date.tm_mday, 11);
  ASSERT_EQ(date.tm_mon, 10);
  ASSERT_EQ(date.tm_year, 2020);
  ASSERT_EQ(date.tm_wday, 3);

  EXPECT_THROW(Date::CreateDate(-11,-15,-1231,-11), std::runtime_error);
  EXPECT_THROW(Date::CreateDate(1252,125326,1253621,77177), std::runtime_error);

}

TEST_F(TestDateNamespaceClass, TestCurrentTimeCorrect){
  time_t t = std::time(0);   // get time now
  tm* now = std::localtime(&t);

  tm currentTime = Date::GetCurrentTime();
  ASSERT_EQ(mktime(now), mktime(&currentTime));
  now->tm_mon--;
  ASSERT_NE(mktime(now),mktime(&currentTime));
}

TEST_F(TestDateNamespaceClass, TestIsToday){
  tm currentTime = Date::GetCurrentTime();
  tm testDate = currentTime;
  ASSERT_EQ(mktime(&currentTime), mktime(&testDate));
  testDate.tm_mday++;
  ASSERT_NE(mktime(&currentTime), mktime(&testDate));
}

TEST_F(TestDateNamespaceClass, TestIsThisWeek){
  tm testDate = Date::GetCurrentTime();
  ASSERT_TRUE(Date::IsThisWeek(testDate));
  testDate.tm_mday+=7;
  ASSERT_FALSE(Date::IsThisWeek(testDate));
}