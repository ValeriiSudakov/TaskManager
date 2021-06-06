/*!
* Copyright (c) 2021 by Cisco Systems, Inc.
* All rights reserved.
*/
//

#ifndef TASKMANAGER_SRC_CLI_STATES_SHOWSTATES_SHOWBYDATESTATE_H_
#define TASKMANAGER_SRC_CLI_STATES_SHOWSTATES_SHOWBYDATESTATE_H_
#include "State.h"

class ShowByDateState : public State {
 public:
  ShowByDateState();
  ~ShowByDateState();

 public:
  ShowByDateState        Do(const std::shared_ptr<Context>& context, InputOutputLayer& io) override;
};


#endif //TASKMANAGER_SRC_CLI_STATES_SHOWSTATES_SHOWBYDATESTATE_H_
