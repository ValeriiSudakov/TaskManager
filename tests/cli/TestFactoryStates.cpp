//
// Created by valeriisudakov on 13.09.20.
//

#include "Factory/FactoryStates.h"
#include <gtest/gtest.h>

class TestFactoryStates :  public ::testing::Test {

};

TEST_F(TestFactoryStates, shouldCreateCorrectState){
  FactoryStates factory;
  auto addTask = factory.Create(StatesID::ADD_TASK);
  ASSERT_EQ(addTask->GetStateID(), StatesID::ADD_TASK);

  auto addSubtask = factory.Create(StatesID::ADD_SUBTASK);
  ASSERT_EQ(addSubtask->GetStateID(), StatesID::ADD_SUBTASK);

  auto postpone = factory.Create(StatesID::POSTPONE);
  ASSERT_EQ(postpone->GetStateID(), StatesID::POSTPONE);

  auto complete = factory.Create(StatesID::COMPLETE);
  ASSERT_EQ(complete->GetStateID(), StatesID::COMPLETE);

  auto remove = factory.Create(StatesID::DELETE);
  ASSERT_EQ(remove->GetStateID(), StatesID::DELETE);

  auto inputName = factory.Create(StatesID::INPUT_NAME);
  ASSERT_EQ(inputName->GetStateID(), StatesID::INPUT_NAME);

  auto inputLabel = factory.Create(StatesID::INPUT_LABEL);
  ASSERT_EQ(inputLabel->GetStateID(), StatesID::INPUT_LABEL);

  auto inputDate = factory.Create(StatesID::INPUT_DATE);
  ASSERT_EQ(inputDate->GetStateID(), StatesID::INPUT_DATE);

  auto inputFileName = factory.Create(StatesID::INPUT_FILE_NAME);
  ASSERT_EQ(inputFileName->GetStateID(), StatesID::INPUT_FILE_NAME);

  auto inputPriority = factory.Create(StatesID::INPUT_PRIORITY);
  ASSERT_EQ(inputPriority->GetStateID(), StatesID::INPUT_PRIORITY);

  auto inputTask = factory.Create(StatesID::INPUT_TASK);
  ASSERT_EQ(inputTask->GetStateID(), StatesID::INPUT_TASK);

  auto baseMenu = factory.Create(StatesID::BASE_MENU);
  ASSERT_EQ(baseMenu->GetStateID(), StatesID::BASE_MENU);

  auto continueMenu = factory.Create(StatesID::CONTINUE_MENU);
  ASSERT_EQ(continueMenu->GetStateID(), StatesID::CONTINUE_MENU);

  auto showAll = factory.Create(StatesID::SHOW_ALL);
  ASSERT_EQ(showAll->GetStateID(), StatesID::SHOW_ALL);

  auto showByID = factory.Create(StatesID::SHOW_BY_ID);
  ASSERT_EQ(showByID->GetStateID(), StatesID::SHOW_BY_ID);

  auto showByLabel = factory.Create(StatesID::SHOW_BY_LABEL);
  ASSERT_EQ(showByLabel->GetStateID(), StatesID::SHOW_BY_LABEL);

  auto showByName = factory.Create(StatesID::SHOW_BY_NAME);
  ASSERT_EQ(showByName->GetStateID(), StatesID::SHOW_BY_NAME);

  auto showToday = factory.Create(StatesID::SHOW_TODAY);
  ASSERT_EQ(showToday->GetStateID(), StatesID::SHOW_TODAY);

  auto showWeek = factory.Create(StatesID::SHOW_THIS_WEEK);
  ASSERT_EQ(showWeek->GetStateID(), StatesID::SHOW_THIS_WEEK);

  auto save = factory.Create(StatesID::SAVE);
  ASSERT_EQ(save->GetStateID(), StatesID::SAVE);

  auto load = factory.Create(StatesID::LOAD);
  ASSERT_EQ(load->GetStateID(), StatesID::LOAD);

  auto Exit = factory.Create(StatesID::EXIT);
  ASSERT_EQ(Exit, nullptr);
}
