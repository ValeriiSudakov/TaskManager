//
// Created by valeriisudakov on 31.08.20.
//

#ifndef TASKMANAGER_CLI_IO_LAYERINTERFACE_H_
#define TASKMANAGER_CLI_IO_LAYERINTERFACE_H_
#include <iostream>

class IO_LayerInterface {
 public:
  virtual ~IO_LayerInterface() = default;

  virtual std::string Input() const = 0;
  virtual void Output(const std::string& str) const = 0;
};


#endif //TASKMANAGER_CLI_IO_LAYERINTERFACE_H_
