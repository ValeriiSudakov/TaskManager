//
// Created by valeriisudakov on 31.08.20.
//

#ifndef TASKMANAGER_CLI_INPUTOUTPUTCONSOLELAYER_H_
#define TASKMANAGER_CLI_INPUTOUTPUTCONSOLELAYER_H_
#include "InputOutputLayer.h"

class InputOutputConsoleLayer : public InputOutputLayer{
 public:
  std::string Input() const override {
    std::string str;
    std::getline(std::cin, str);
    return str;
  }
  void Output(const std::string& str) const{
    std::cout<<str;
  }
};

#endif //TASKMANAGER_CLI_INPUTOUTPUTCONSOLELAYER_H_
