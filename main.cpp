#include "cli/Context.h"
#include "cli/States/AddTaskState.h"
#include "cli/States/State.h"
#include "cli/States/BaseState.h"

int main(){
  std::shared_ptr<Context> context;
  context->TransitionTo(std::make_shared<BaseState>("base task", context));
  context->Request();
  return 0;
}
