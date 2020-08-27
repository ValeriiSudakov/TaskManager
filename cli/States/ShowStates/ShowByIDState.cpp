//
// Created by valeriisudakov on 25.08.20.
//

#include "ShowByIDState.h"
#include "States/BaseState.h"
#include "Factory.h"
ShowByIDState::ShowByIDState(){
  stateName_ = "show by id";
}

ShowByIDState::~ShowByIDState() = default;

void ShowByIDState::Do(const std::shared_ptr<Context>& context) {
  auto task = context->taskService_->GetTask(context->buffer_.id);
  if (task.has_value()){
    std::cout<<task.value().ToString()<<std::endl;
    return;
  }
  std::cout<<"Task was not found.\n";
}

std::shared_ptr<State> ShowByIDState::ReadAction() {
  return Factory::CreateState(StatesList::Base);
}