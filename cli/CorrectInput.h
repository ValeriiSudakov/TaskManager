//
// Created by valeriisudakov on 20.08.20.
//

#ifndef TASKMANAGER_CLI_CORRECTINPUT_H_
#define TASKMANAGER_CLI_CORRECTINPUT_H_
#include "Date/Date.h"
#include "API/Priority.h"
#include <optional>

namespace CorrectInput {
  static std::optional<std::string> Name() {
    std::string name;
    std::getline(std::cin, name);
    if (name.empty()) {
      return nullptr;
    }
    return std::make_optional(name);
  }

static std::optional<std::string> Label() {
    std::string label;
    std::getline(std::cin, label);
    if (label.empty()) {
      return nullptr;
    }
    return std::make_optional(label);
  }

static std::optional<Priority> Priority() {
    std::string priorityStr;
    std::getline(std::cin, priorityStr);
    if (priorityStr == "first" || priorityStr == "1") {
      return std::make_optional(Priority::FIRST);
    } else if (priorityStr == "second" || priorityStr == "2") {
      return std::make_optional(Priority::SECOND);
    } else if (priorityStr == "third" || priorityStr == "3") {
      return std::make_optional(Priority::THIRD);
    } else if (priorityStr == "none" || priorityStr == "0" || priorityStr == "") {
      return std::make_optional(Priority::NONE);
    } else {
      return std::nullopt;
    }
  }

  static std::optional<Date> Date() {
    std::string dateStr;
    std::getline(std::cin, dateStr);
    if (dateStr == "now") {
      return std::make_optional(Date::GetCurrentTime());
    } else {
      try {
        return std::make_optional(dateStr);
      } catch (const std::exception &ex) {
        return std::nullopt;
      }
    }
  }
}
#endif //TASKMANAGER_CLI_CORRECTINPUT_H_
