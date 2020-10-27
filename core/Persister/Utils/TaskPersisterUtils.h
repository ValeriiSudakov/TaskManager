//
// Created by valeriisudakov on 30.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
#define TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
#include "Repository/TaskRepository.h"
#include "RepositoryData.pb.h"

/*
 * Persister utils.
 *
 * @author: Valerii Sudakov.
 */
class Persister;

namespace persister_utils{
/*
 * Convert function from proto::Priority to Priority.
 *
 * @param: proto::Priority.
 *
 * @return-type: Priority.
 */
  Priority                              SerializedPriorityToPriority(const proto::Priority& priority);

/*
 * Convert function from Priority to proto::Priority.
 *
 * @param: Priority.
 *
 * @return-type: proto::Priority.
 */
  proto::Priority                  PriorityToSerializedPriority(const Priority& priority);

/*
 * Convert function from TaskRepositoryDTO to proto::Task
 *
 * @param: reference to TaskRepository - data to source.
 * @param: reference to proto::Task - destination of data.
 */
  void                                  SerializedTaskFromDTO(const TaskRepositoryDTO& taskDTO,
                                                              proto::Task& task);

/*
 * Add subtasks to proto::Task.
 * Recursive function. Takes subtasks of TaskRepositoryDTO and
 * set it to proto::Task.
 *
 * @param: proto::Task - destination of data.
 * @param: TaskRepositoryDTO - contains root ID of subtasks
 * @param: TaskRepository - data source of tasks.
 */
  void                                  AddSubtasks(proto::Task& serializedTask, TaskRepositoryDTO& task,
                                                    TaskRepository& repository_);

/*
 * Add subtasks to Repository.
 * Recursive function. Takes subtasks of proto::Task and
 * set it to TaskRepository.
 *
 * @param: TaskRepository - destination of data.
 * @param: TaskID - id of root task to add subtasks.
 * @param: SerializedTask - data source of tasks.
 */

  void                                  AddSubtasksToRepository(const proto::Task& serializedTask, TaskID& rootID,
                                                                TaskRepository& repository_);

/*
 * Convert function from proto::Task To TaskRepositoryDTO.
 *
 * @param: proto::Task - source of data to convert.
 *
 * @return-type: TaskRepositoryDTO if converted success, nullopt if not.
 */
  std::optional<TaskRepositoryDTO>      DTOFromSerializedTask(const proto::Task& task);

/*
 * Factory method of TaskPersister.
 *
 * @param: TaskRepository - repository of tasks.
 * @param: std::fstream - stream to save/load data.
 */
  std::unique_ptr<Persister>            Create(TaskRepository& repository, std::fstream& stream);
}

#endif //TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
