//
// Created by R2D2 on 30.07.2020.
//

#include "TaskIDGenerate.h"

TaskIDGenerate::TaskIDGenerate() : id_(0){}

std::uint32_t TaskIDGenerate::Generate() {
  return id_++;
}