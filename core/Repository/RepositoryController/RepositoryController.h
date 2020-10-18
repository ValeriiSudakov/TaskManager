//
// Created by valeriisudakov on 06.10.20.
//

#ifndef TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_REPOSITORYCONTROLLER_H_
#define TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_REPOSITORYCONTROLLER_H_
#include <memory>
#include "Repository/TaskRepository.h"

/*
 *  Owner of the TaskRepository class.
 *  He is responsible for create and delete it.
 *
 *  @author: Valerii Sudakov
 */
class RepositoryController {
 public:
  virtual ~RepositoryController() = default;

/*
 * Get method of Repository to provide ability to use methods of it.
 *
 * @return-type: const reference to unique_ptr of TaskRepository.
 */
  virtual const std::unique_ptr<TaskRepository>&            Get() const = 0;

/*
 * Saves all tasks of the system.
 *
 * @param: const string reference, that contains file name to save tasks.
 *
 * @return-type: true if operation success, false if not.
 */
  virtual bool                                              Save(const std::string& filename) = 0;

/*
 * Loads tasks of the system.
 * If operation success, all tasks will be deleted and changed by new.
 * If not - nothing will changes.
 *
 * @param: const string reference, that contains file name to load tasks.
 *
 * @return-type: true if operation success, false if not.
 */
  virtual bool                                              Load(const std::string& filename) = 0;
};

#endif //TASKMANAGER_CORE_MEMORY_MODEL_STORAGE_REPOSITORYCONTROLLER_H_
