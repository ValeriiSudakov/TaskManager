//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_STATESLIST_H_
#define TASKMANAGER_CLI_STATESLIST_H_

enum class StatesList{
  ShowAll,
  ShowByID,
  ShowByLabel,
  ShowByName,
  ShowThisWeek,
  ShowToday,
  AddTask,
  AddSubtask,
  Complete,
  Delete,
  Postpone,
  Base
};

enum class InputStatesList{
  InputID,
  InputDate,
  InputPriority,
  InputLabel,
  InputName,
};

#endif //TASKMANAGER_CLI_STATESLIST_H_
