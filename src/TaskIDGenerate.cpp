//
// Created by R2D2 on 30.07.2020.
//

#include "TaskIDGenerate.h"

TaskIDGenerate::TaskIDGenerate() : id(0){}

unsigned int TaskIDGenerate::Generate() {
  return id++;
}