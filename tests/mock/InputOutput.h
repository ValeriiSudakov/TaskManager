//
// Created by valeriisudakov on 05.10.20.
//

#ifndef TASKMANAGER_TESTS_MOCK_INPUTOUTPUT_H_
#define TASKMANAGER_TESTS_MOCK_INPUTOUTPUT_H_
#include "InputOutputLayer.h"

class MockIO : public InputOutputLayer{
 public:
  MOCK_METHOD(std::string, Input, (), (override));
  MOCK_METHOD(void, Output, (const std::string&), (override));
};
#endif //TASKMANAGER_TESTS_MOCK_INPUTOUTPUT_H_
