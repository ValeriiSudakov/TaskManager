//
// Created by valeriisudakov on 27.08.20.
//

#ifndef TASKMANAGER_CLI_STATESLIST_H_
#define TASKMANAGER_CLI_STATESLIST_H_

enum class StatesID{
  SHOW,
  EDIT,
  SHOW_ALL,
  SHOW_BY_ID,
  SHOW_BY_LABEL,
  SHOW_BY_NAME,
  SHOW_BY_DATE,
  SHOW_THIS_WEEK,
  SHOW_TODAY,

  ADD_TASK,
  ADD_SUBTASK,
  COMPLETE,
  DELETE,
  POSTPONE,
  SAVE,
  LOAD,

  INPUT_TASK,
  INPUT_ID,
  INPUT_DATE,
  INPUT_PRIORITY,
  INPUT_LABEL,
  INPUT_NAME,
  INPUT_FILE_NAME,

  BASE_MENU,
  CONTINUE_MENU,
  EXIT
};


#endif //TASKMANAGER_CLI_STATESLIST_H_
