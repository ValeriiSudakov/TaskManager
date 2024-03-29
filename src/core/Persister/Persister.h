//
// Created by valeriisudakov on 29.09.20.
//

#ifndef TASKMANAGER_CORE_PERSISTER_PERSISTER_H_
#define TASKMANAGER_CORE_PERSISTER_PERSISTER_H_

/*
 * Persister interface.
 * Provides methods to save/load data.
 *
 * @author: Valerii Sudakov.
 */
class Persister {
 public:
  virtual ~Persister() = default;

  virtual bool Save() = 0;
  virtual bool Load() = 0;
};

#endif //TASKMANAGER_CORE_PERSISTER_PERSISTER_H_
