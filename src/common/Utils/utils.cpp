/*!
* Copyright (c) 2021 by Cisco Systems, Inc.
* All rights reserved.
*/
//

#include "utils.h"

Priority SerializedPriorityToPriority(const proto::Priority& priority){
  if (proto::Priority::FIRST == priority){
    return Priority::FIRST;
  } else if (proto::Priority::SECOND == priority){
    return Priority::SECOND;
  } else if (proto::Priority::THIRD == priority){
    return Priority::THIRD;
  } else if (proto::Priority::NONE == priority) {
    return Priority::NONE;
  }
  return Priority::NONE;
}
