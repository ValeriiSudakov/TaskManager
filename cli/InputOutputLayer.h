//
// Created by valeriisudakov on 31.08.20.
//

#ifndef TASKMANAGER_CLI_INPUTOUTPUTLAYER_H_
#define TASKMANAGER_CLI_INPUTOUTPUTLAYER_H_
#include <iostream>

class InputOutputLayer {
 public:
  virtual ~InputOutputLayer() = default;

  virtual std::string Input() const = 0;
  virtual void Output(const std::string& str) const = 0;
};


#endif //TASKMANAGER_CLI_INPUTOUTPUTLAYER_H_
