/*!
* Copyright (c) 2021 by Cisco Systems, Inc.
* All rights reserved.
*/
//

#ifndef TASKMANAGER_SRC_COMMON_UTILS_UTILS_H_
#define TASKMANAGER_SRC_COMMON_UTILS_UTILS_H_
#include "Priority.h"
#include "Priority.pb.h"

/*
 * Convert function from proto::Priority to Priority.
 *
 * @param: proto::Priority.
 *
 * @return-type: Priority.
 */
Priority SerializedPriorityToPriority(const proto::Priority& priority);

#endif //TASKMANAGER_SRC_COMMON_UTILS_UTILS_H_
