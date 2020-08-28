//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_STATESLIST_H_
#define TASKMANAGER_CLI_STATESLIST_H_

enum class StatesID{
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

  InputID,
  InputDate,
  InputPriority,
  InputLabel,
  InputName,
  EditInput,

  Exit,
  Base
};


#endif //TASKMANAGER_CLI_STATESLIST_H_
