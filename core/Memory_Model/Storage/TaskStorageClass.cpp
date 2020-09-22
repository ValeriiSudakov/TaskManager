//
//
// Created by valerii.sudakov on 8/4/2020.


#include "TaskStorageClass.h"
#include "SerializeModel.pb.h"
#include <fstream>

SerializedTask::Priority PriorityToSerializedPriority(const Priority& priority);
Priority SerializedPriorityToPriority(const SerializedTask::Priority& priority);

TaskStorageClass::TaskStorageClass() = default;

std::optional<std::shared_ptr<TaskEntity>> TaskStorageClass::AddTask(const Task& task){
  TaskID newTaskID = taskIDGenerate_.Generate();
  auto newEntityTask = std::make_shared<TaskEntity>(task, newTaskID);
  tasks_.insert(std::make_pair(newTaskID, newEntityTask));
  return newEntityTask;
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorageClass::AddSubtask(const TaskID &rootTaskID, const Task &subtask) {

  auto task = tasks_.find(rootTaskID);
  if (task != tasks_.end()){ // if task exist
    TaskID newTaskID = taskIDGenerate_.Generate();
    auto newEntityTask = std::make_shared<TaskEntity>(subtask, TaskID(newTaskID), rootTaskID);

    task->second->AddSubtasks(newEntityTask);
    tasks_.insert(std::make_pair(newTaskID, newEntityTask));

    return newEntityTask;
  }

  return std::nullopt;
}

std::optional<std::shared_ptr<TaskEntity>> TaskStorageClass::GetTask(const TaskID& taskID) const{
  auto task = tasks_.find(taskID);
  return (task == tasks_.end()) ? std::nullopt : std::make_optional(task->second);
}

bool TaskStorageClass::RemoveTask(const TaskID &id) {
  auto task = tasks_.find(id);
  if (task != tasks_.end()){
    task->second.reset();
    tasks_.erase(task);
    return true;
  }
  return false;
}


bool TaskStorageClass::PostponeTask(const TaskID& id, const Date& date){
  auto task = tasks_.find(id);
  if (task != tasks_.end()){
    auto result = task->second->PostponeDate(date);
    return result;
  }
  return false;
}

bool TaskStorageClass::LoadFromFile(const std::string &fileName) {
  if (fileName == ""){
    return false;
  }
  return DeserializeStorage(fileName);
}

bool TaskStorageClass::SaveToFile(const std::string &fileName) {
  if(fileName == ""){
    return false;
  }
  return SerializeStorage(fileName);
}

bool TaskStorageClass::DeserializeStorage(const std::string& fileName){
  tasks_.clear();
  taskIDGenerate_ = TaskIDGenerate(0);
  SerializedStorage storage;
  std::ifstream file(fileName);

  if (!file.is_open()){
    return false;
  }

  storage.ParseFromIstream(&file);
  file.close();

  for (const auto& task : storage.tasks()){
    auto newTask = Task::Create(task.task().name(),
                                task.task().label(),
                                SerializedPriorityToPriority(task.task().priority()),
                                boost::gregorian::date(task.task().date()));

    std::optional<std::shared_ptr<TaskEntity>> createdTask;
    if (task.rootid() == task.id()){
      createdTask = AddTask(newTask.value());
    } else {
      createdTask = AddSubtask(TaskID(task.rootid()), newTask.value());
    }
   if (task.complete()) {
     createdTask.value()->SetComplete();
    }
  }
  return true;
}

bool TaskStorageClass::SerializeStorage(const std::string& fileName) {
  //      oldID  newID
  std::map<TaskID, std::uint32_t> idMapping;

  int i = 0;
  for (const auto &task : tasks_) {
    idMapping[task.first] = i;
    i++;
  }
  SerializedStorage storageToSave;

  for (const auto &task : tasks_) {
    auto *addTask = storageToSave.add_tasks();
    auto newTask = std::make_unique<SerializedTask>();

    newTask->set_name(task.second->GetName());
    newTask->set_label(task.second->GetLabel());
    newTask->set_priority(PriorityToSerializedPriority(task.second->GetPriority()));
    newTask->set_date(task.second->GetDueDate().Get().day_number());
    addTask->set_allocated_task(newTask.release());

    addTask->set_id(idMapping[task.first]);
    addTask->set_rootid(idMapping[task.second->GetParentId()]);
    addTask->set_complete(task.second->IsComplete());

    for (const auto &subID : task.second->GetSubtasks()) {
      addTask->add_subtasks(idMapping[subID.first]);
    }
  }

  std::ofstream file(fileName);
  if (!file.is_open()) {
    return false;
  }

  storageToSave.SerializeToOstream(&file);
  file.close();
  return true;
}

SerializedTask::Priority PriorityToSerializedPriority(const Priority& priority){
  if (Priority::FIRST == priority){
    return SerializedTask::Priority::SerializedTask_Priority_FIRST;
  } else if (Priority::SECOND == priority){
    return SerializedTask::Priority::SerializedTask_Priority_SECOND;
  } else if (Priority::THIRD == priority){
    return SerializedTask::Priority::SerializedTask_Priority_THIRD;
  } else if (Priority::NONE == priority) {
    return SerializedTask::Priority::SerializedTask_Priority_NONE;
  }
}

Priority SerializedPriorityToPriority(const SerializedTask::Priority& priority){
  if (SerializedTask::Priority::SerializedTask_Priority_FIRST == priority){
    return Priority::FIRST;
  } else if (SerializedTask::Priority::SerializedTask_Priority_SECOND == priority){
    return Priority::SECOND;
  } else if (SerializedTask::Priority::SerializedTask_Priority_THIRD == priority){
    return Priority::THIRD;
  } else if (SerializedTask::Priority::SerializedTask_Priority_NONE == priority) {
    return Priority::NONE;
  }
}