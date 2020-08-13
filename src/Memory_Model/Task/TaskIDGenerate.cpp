//
// Created by R2D2 on 30.07.2020.
//

#include "TaskIDGenerate.h"

TaskIDGenerate::TaskIDGenerate() : id_(0){}

TaskID TaskIDGenerate::Generate() {
  return TaskID(id_++);
}