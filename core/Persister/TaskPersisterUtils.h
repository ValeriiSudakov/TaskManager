//
// Created by valeriisudakov on 30.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
#define TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
#include "Memory_Model/Storage/TaskRepository.h"
#include "SerializedModel.pb.h"

/*
 * Persister utils.
 *
 * @author: Valerii Sudakov.
 */
class Persister;

namespace PersisterUtils{
/*
 * Convert function from Serialized::Priority to Priority.
 *
 * @param: Serialized::Priority.
 *
 * @return-type: Priority.
 */
  Priority                              SerializedPriorityToPriority(const Serialized::Priority& priority);

/*
 * Convert function from Priority to Serialized::Priority.
 *
 * @param: Priority.
 *
 * @return-type: Serialized::Priority.
 */
  Serialized::Priority                  PriorityToSerializedPriority(const Priority& priority);

/*
 * Convert function from TaskRepositoryDTO to Serialized::Task
 *
 * @param: reference to TaskRepository - data to source.
 * @param: reference to Serialized::Task - destination of data.
 */
  void                                  SerializedTaskFromDTO(const TaskRepositoryDTO& taskDTO,
                                                              Serialized::Task& task);

/*
 * Add subtasks to Serialized::Task.
 * Recursive function. Takes subtasks of TaskRepositoryDTO and
 * set it to Serialized::Task.
 *
 * @param: Serialized::Task - destination of data.
 * @param: TaskRepositoryDTO - contains root ID of subtasks
 * @param: TaskRepository - data source of tasks.
 */
  void                                  AddSubtasks(Serialized::Task& serializedTask, TaskRepositoryDTO& task,
                                                    TaskRepository& repository_);

/*
 * Add subtasks to Repository.
 * Recursive function. Takes subtasks of Serialized::Task and
 * set it to TaskRepository.
 *
 * @param: TaskRepository - destination of data.
 * @param: TaskID - id of root task to add subtasks.
 * @param: SerializedTask - data source of tasks.
 */

  void                                  AddSubtasksToRepository(const Serialized::Task& serializedTask, TaskID& rootID,
                                                                TaskRepository& repository_);

/*
 * Convert function from Serialized::Task To TaskRepositoryDTO.
 *
 * @param: Serialized::Task - source of data to convert.
 *
 * @return-type: TaskRepositoryDTO if converted success, nullopt if not.
 */
  std::optional<TaskRepositoryDTO>      DTOFromSerializedTask(const Serialized::Task& task);

/*
 * Factory method of TaskPersister.
 *
 * @param: TaskRepository - repository of tasks.
 * @param: std::fstream - stream to save/load data.
 */
  std::unique_ptr<Persister>            Create(TaskRepository& repository, std::fstream& stream);
}

#endif //TASKMANAGER_CORE_PERSISTER_TASKPERSISTERUTILS_H_
