//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepository.h"
TaskRepository::TaskRepository() : taskIDGenerate_(TaskIDGenerate()) {}
TaskRepository::~TaskRepository() = default;


void TaskRepository::AddTask(const Task& task, const Task::Priority& priority){
  TaskID newTaskID = taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));

  taskView_.AddTask(newEntityTask);
}

bool TaskRepository::AddSubtask(const TaskID &rootTaskID, const Task &subtask,
                                                          const Task::Priority &priority) {

  if (tasks_.find(rootTaskID.GetID()) != tasks_.end()){ // if task exist
    TaskID newTaskID = taskIDGenerate_.Generate();
    auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(newTaskID));

    tasks_[rootTaskID.GetID()]->AddSubtasks(newEntityTask);
    tasks_.insert(std::make_pair(newTaskID.GetID(), newEntityTask));

    taskView_.AddTask(newEntityTask);
    return true;
  }
  return false;
}

std::optional<std::shared_ptr<TaskEntity>> TaskRepository::GetTask(const TaskID &taskID) {
  if (tasks_.find(taskID.GetID()) == tasks_.end()) {
    return std::nullopt;
  } else {
    return tasks_[taskID.GetID()];
  }
}

std::vector<TaskEntity>  TaskRepository::GetTasks() {
  return taskView_.GetTasks();
}

std::vector<TaskEntity>  TaskRepository::GetTodayTasks(){
  return taskView_.GetTodayTasks();
}

std::vector<TaskEntity>  TaskRepository::GetWeekTasks(){
  return taskView_.GetWeekTasks();
}

std::vector<TaskEntity>  TaskRepository::GetTasksByLabel(const std::string& label){
  return taskView_.GetTasksByLabel(label);
}

std::vector<TaskEntity>  TaskRepository::GetTasksByName(const std::string& name){
  return taskView_.GetTasksByName(name);
}

std::vector<TaskEntity>  TaskRepository::GetTasksByPriority(Task::Priority taskPriority){
  return taskView_.GetTasksByPriority(taskPriority);
}
