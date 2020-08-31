//
// Created by R2D2 on 15.07.2020.
//

#include "TaskService.h"
#include <string>
#include <vector>

TaskService TaskService::Create(){
  return TaskService(std::move(std::make_unique<TaskRepository>(std::move(std::make_unique<TaskView>()),
                                                                    std::move(std::make_unique<TaskStorage>()))));
}

TaskService::TaskService(std::unique_ptr<TaskRepositoryInterface> taskRepository)
  : tasksRepository_(std::move(taskRepository)) {

}

AddTaskResult TaskService::AddTask(const TaskDTO& task){
  AddTaskResult addNewTask = tasksRepository_->AddTask(task);
  return addNewTask.success_;
}

AddTaskResult TaskService::AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask){
  auto addNewSubtask = tasksRepository_->AddSubtask(rootTaskID, subtask);
  return addNewSubtask.success_;
}

bool TaskService::RemoveTask(const TaskID& ID){
  auto result = tasksRepository_->RemoveTask(ID);
  return result;
}


bool TaskService::PostponeTask(const TaskID& ID, const Date& date){
  return tasksRepository_->PostponeTask(ID, date);
}

bool TaskService::SetTaskComplete(const TaskID &ID) {
  auto task = tasksRepository_->GetTaskStorage()->GetTask(ID);
  if (!task.has_value()){
    return false;
  }
  task.value()->SetComplete();
  return true;
}

std::optional<TaskDTO> TaskService::GetTask(const TaskID& id) const{
  auto task = tasksRepository_->GetTaskStorage()->GetTask(id);return task.has_value() ? std::make_optional(TaskDTO::Create(task.value()->GetName(), task.value()->GetLabel(),
                                                                             task.value()->GetPriority(), task.value()->GetDueDate(),
                                                                             task.value()->IsComplete(), task.value()->GetId())) : std::nullopt;
}

std::vector<TaskDTO> TaskService::GetTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasks();
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTodayTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTodayTasks();
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetWeekTasks(bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetWeekTasks();
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByLabel(const std::string& label, bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasksByLabel(label);
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByName(const std::string& name, bool byPriority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasksByName(name);
  return byPriority ? convertor::toTaskDTO::sortedVectorByPriority(sortedTasks) : convertor::toTaskDTO::notSortedVector(sortedTasks);
}

std::vector<TaskDTO> TaskService::GetTasksByPriority(const Priority& priority) const{
  auto sortedTasks = tasksRepository_->GetTaskView()->GetTasksByPriority(priority);
  return convertor::toTaskDTO::notSortedVector(sortedTasks);
}

