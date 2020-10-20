//
// Created by valeriisudakov on 20.10.20.
//

#include <gtest/gtest.h>
#include "API/DTO/Utils/TaskServiceDTOUtils.h"

class TestTaskServiceDTOUtils : public ::testing::Test {

};


TEST_F(TestTaskServiceDTOUtils, shoultConvertPriorityToString){
  ASSERT_EQ("first", task_service_dto_utils::PriorityToString(Priority::FIRST));
  ASSERT_EQ("second", task_service_dto_utils::PriorityToString(Priority::SECOND));
  ASSERT_EQ("third", task_service_dto_utils::PriorityToString(Priority::THIRD));
  ASSERT_EQ("none", task_service_dto_utils::PriorityToString(Priority::NONE));
}