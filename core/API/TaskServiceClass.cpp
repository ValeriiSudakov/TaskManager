//
// Created by R2D2 on 15.07.2020.
//

#include "TaskServiceClass.h"
#include <string>
#include <vector>

TaskServiceClass TaskServiceClass::Create(){
  return TaskServiceClass(std::move(std::make_unique<TaskRepositoryClass>(std::move(std::make_unique<TaskViewClass>()),
                                                                          std::move(std::make_unique<TaskStorageClass>()))));
}

TaskServiceClass::TaskServiceClass(std::unique_ptr<TaskRepository> taskRepository)
  : tasksRepository_(std::move(taskRepository)) {

}

AddTaskResult TaskServiceClass::AddTask(const TaskServiceDTO& task){
  auto transformTask = Task::Create(task.GetName(), task.GetLabel(), task.GetPriority(), task.GetDate());
  if (!transformTask.has_value()){
    return AddTaskResult(AddTaskResult::ErrorType::TASK_IS_DAMAGED, false);
  }
  AddTaskResult addNewTask = tasksRepository_->AddTask(transformTask.value());
  return addNewTask.success_;
}

AddTaskResult TaskServiceClass::AddSubtask(const TaskID& rootTaskID, const TaskServiceDTO& subtask){
  auto transformTask = Task::Create(subtask.GetName(), subtask.GetLabel(), subtask.GetPriority(), subtask.GetDate());
  if (!transformTask.has_value()){
    return AddTaskResult(AddTaskResult::ErrorType::TASK_IS_DAMAGED, false);
  }
  auto addNewSubtask = tasksRepository_->AddSubtask(rootTaskID, transformTask.value());
  return addNewSubtask.success_;
}

bool TaskServiceClass::RemoveTask(const TaskID& ID){
  auto result = tasksRepository_->RemoveTask(ID);
  return result;
}


bool TaskServiceClass::PostponeTask(const TaskID& ID, const Date& date){
  return tasksRepository_->PostponeTask(ID, date);
}

bool TaskServiceClass::SetTaskComplete(const TaskID &ID) {
  auto task = tasksRepository_->GetTaskStorage()->GetTask(ID);
  if (!task.has_value()){
    return false;
  }
  task.value()->SetComplete();
  return true;
}

std::optional<TaskServiceDTO> TaskServiceClass::GetTask(const TaskID& id) const{
  auto task = tasksRepository_->GetTaskStorage()->GetTask(id);
  return task.has_value() ? std::make_optional(TaskServiceDTO::Create(task.value()->GetName(), task.value()->GetLabel(),
                                                                              task.value()->GetPriority(), task.value()->GetDueDate(),
                                                                              task.value()->IsComplete(), task.value()->GetId())) : std::nullopt;
}

std::vector<TaskServiceDTO> TaskServiceClass::GetSubtask(const TaskID& id) const{
  auto subtasks = tasksRepository_->GetTaskStorage()->GetTask(id).value()->GetSubtasks();
  std::vector<TaskEntity> temp;
  for (auto const& task : subtasks){
    temp.push_back(*task.second.lock());
  }
  return convertor::toTaskDTO::notSortedVector(temp);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasks();
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTodayTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTodayTasks();
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetWeekTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetWeekTasks();
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByLabel(const std::string& label, bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasksByLabel(label);
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByName(const std::string& name, bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasksByName(name);
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskServiceDTO> TaskServiceClass::GetTasksByPriority(const Priority& priority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasksByPriority(priority);
  return convertor::toTaskDTO::notSortedVector(sortedTasks);
}

