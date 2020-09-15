//
// Created by R2D2 on 16.07.2020.
//

#include <gtest/gtest.h>
#include "API/TaskServiceClass.h"
#include <iostream>
#include <stdexcept>

class TestDate : public ::testing::Test {

};


TEST_F(TestDate, shouldCreateDate){
  Date d1(Date::GetCurrentTime());
  ASSERT_FALSE(d1.Get().is_not_a_date());
  Date d2("2005/2/7");
  ASSERT_FALSE(d2.Get().is_not_a_date());
  Date d3("5213-4-1");
  ASSERT_FALSE(d3.Get().is_not_a_date());
  Date d4("1532/-12/-11");
  ASSERT_FALSE(d4.Get().is_not_a_date());
}

TEST_F(TestDate, shouldntCreateDate){
  ASSERT_ANY_THROW(Date("-1231-1-0"));
  ASSERT_ANY_THROW(Date("141221231-1-0"));
  ASSERT_ANY_THROW(Date(""));
  ASSERT_ANY_THROW(Date("asda14sa0"));
  ASSERT_ANY_THROW(Date("2000/12312/21"));
  ASSERT_ANY_THROW(Date("2024/4534/11"));
  ASSERT_ANY_THROW(Date("2024/21/124124"));
  ASSERT_ANY_THROW(Date("2024/21"));
  ASSERT_ANY_THROW(Date("2024"));
  ASSERT_ANY_THROW(Date("2024/21/"));
  ASSERT_ANY_THROW(Date("2024/21/124124/"));
  ASSERT_ANY_THROW(Date("321132/21/124124/"));
  ASSERT_ANY_THROW(Date("0/21/124124/"));
  ASSERT_ANY_THROW(Date("today"));
}

TEST_F(TestDate, shouldBeToday){
  ASSERT_TRUE(Date::IsToday(Date::GetCurrentTime()));
}

TEST_F(TestDate, shouldntBeToday){
  ASSERT_FALSE(Date::IsToday(Date("2013-1-1").Get()));
  ASSERT_FALSE(Date::IsToday(Date("2091-3-5").Get()));
  ASSERT_FALSE(Date::IsToday(Date("1434-2-3").Get()));
  ASSERT_FALSE(Date::IsToday(Date("9924-4-4").Get()));
  ASSERT_FALSE(Date::IsToday(Date("8412-12-4").Get()));
  ASSERT_FALSE(Date::IsToday(Date("2041-8-7").Get()));
}

TEST_F(TestDate, shouldBeThisWeek){
  Date date(Date::GetCurrentTime());
  ASSERT_TRUE(Date::IsThisWeek(date.Get()));
}

TEST_F(TestDate, shouldntBeThisWeek){
  Date date(Date::GetCurrentTime());
                                                // calc day after end of week
  Date dayAfterEndOfWeek(boost::gregorian::date(Date::DayForEndOfWeek() + 1));
  ASSERT_FALSE(Date::IsThisWeek(dayAfterEndOfWeek.Get()));
}

TEST_F(TestDate, shouldConvertToString){
  Date d1("2020-2-2");
  Date d2("2020/2/2");
  std::string str1{"2020-02-02"};
  ASSERT_EQ(d1.ToString(), str1);
  ASSERT_EQ(d2.ToString(), str1);
}
