//
// Created by R2D2 on 31.07.2020.
//

#include "TaskRepositoryClass.h"
#include "assert.h"

TaskRepositoryClass::TaskRepositoryClass(std::unique_ptr<TaskView> view, std::unique_ptr<TaskStorage> storage)
 : taskView_(std::move(view)), taskStorage_(std::move(storage)){}

AddTaskResult TaskRepositoryClass::AddTask(const TaskRepositoryDTO &task){
  auto newTaskEntity = EntityFromDTO(task);
  if (!newTaskEntity.has_value()){
    return AddTaskResult::Failed(AddTaskResult::ErrorType::TASK_IS_DAMAGED);
  }
  auto newTask = taskStorage_->AddTask(newTaskEntity.value());
  if (newTask.has_value()) {
    taskView_->AddTask(newTask.value());
    return AddTaskResult::Success(newTask.value()->GetId());
  }
  return AddTaskResult::Failed(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY);
}

AddTaskResult TaskRepositoryClass::AddSubtask(const TaskID& rootTaskID, const TaskRepositoryDTO& subtask){
  auto rootTask = taskStorage_->GetTask(rootTaskID);
  if (!rootTask.has_value()){
    return AddTaskResult::Failed(AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK);
  }

  auto newTaskEntity = EntityFromDTO(subtask);
  if (!newTaskEntity.has_value()){
    return AddTaskResult::Failed(AddTaskResult::ErrorType::NOT_FOUND_PARENT_TASK);
  }
  auto newTask = taskStorage_->AddTask(newTaskEntity.value());
  if (newTask.has_value()) {
    taskView_->AddTask(newTask.value());
    rootTask.value()->AddSubtasks(newTask.value());
    return AddTaskResult::Success(newTask.value()->GetId());
  }

  return AddTaskResult::Failed(AddTaskResult::ErrorType::NOT_ENOUGH_FREE_MEMORY);
}

bool TaskRepositoryClass::RemoveTask(const TaskID& id){
  auto task = taskStorage_->GetTask(id);
  if (!task.has_value()){
    return false;
  }
  std::vector<TaskID> idTaskToDelete;
  for (const auto& subtask : task.value()->GetSubtasks()){
    TaskID subtaskID = subtask.second.lock()->GetId();
    idTaskToDelete.push_back(subtaskID);
    // recursive delete subtasks of those subtasks
    RemoveTask(subtaskID);
  }
  // remove subtasks
  for (const auto& id : idTaskToDelete){
    taskStorage_->RemoveTask(id);
    auto task = taskStorage_->GetTask(id);
    if (task.has_value()){
      taskView_->RemoveTask(task.value());
    }
  }
  // remove task
  taskStorage_->RemoveTask(task.value()->GetId());
  taskView_->RemoveTask(task.value());
  auto taskParentID = task.value()->GetParentId();
  if (taskParentID != task.value()->GetId()){
    taskStorage_->GetTask(taskParentID).value()->RemoveTaskFromSubtasks(id);
  }
  return true;
}


bool TaskRepositoryClass::PostponeTask(const TaskID& id, const Date& date){
  auto oldTask = taskStorage_->GetTask(id);
  if (!oldTask.has_value()){
    return false;
  }
  taskView_->RemoveTask(oldTask.value());
  auto result = taskStorage_->PostponeTask(id, date);
  taskView_->AddTask(taskStorage_->GetTask(id).value());
  return result;
}

bool TaskRepositoryClass::SetTaskComplete(const TaskID &id) {
  auto task = taskStorage_->GetTask(id);
  if (!task.has_value()){
    return false;
  }
  task.value()->SetComplete();
  return true;
}

void TaskRepositoryClass::ResetRepository() {
  taskStorage_.reset();
  taskStorage_ = std::make_unique<TaskStorageClass>();
  taskView_.reset();
  taskView_ = std::make_unique<TaskViewClass>();
}

std::optional<TaskRepositoryDTO> TaskRepositoryClass::GetTask(const TaskID& id) const {

  auto task = taskStorage_->GetTask(id);
  if (!task.has_value()){
    return std::nullopt;
  }
  return DTOFromEntity(*task.value());
}
std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetSubtask(const TaskID& id) const {
  auto task = taskStorage_->GetTask(id);
  std::vector<TaskRepositoryDTO> subtasks;
  if (task.has_value()){
    return subtasks;
  }
  for (const auto& subtask : task.value()->GetSubtasks()){
    subtasks.push_back(DTOFromEntity(*subtask.second.lock()));
  }
  return subtasks;
}

std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetTasks() const{
  auto tasks = taskStorage_->GetTasks();
  std::vector<TaskRepositoryDTO> tasksDTO;
  for (const auto& task : tasks){
    tasksDTO.push_back(DTOFromEntity(*task.second));
  }
  return tasksDTO;
}

std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetTodayTasks(bool byPriority) const {
  auto tasks = taskView_->GetTodayTasks();
  std::vector<TaskRepositoryDTO> tasksDTO;
  for (const auto& task : tasks){
    tasksDTO.push_back(DTOFromEntity(task));
  }
  if (byPriority){
    SortByPriority(tasksDTO);
  }
  return tasksDTO;
}

std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetWeekTasks(bool byPriority) const{
  auto tasks = taskView_->GetWeekTasks();
  std::vector<TaskRepositoryDTO> tasksDTO;
  for (const auto& task : tasks){
    tasksDTO.push_back(DTOFromEntity(task));
  }
  if (byPriority){
    SortByPriority(tasksDTO);
  }
  return tasksDTO;
}

std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetTasksByLabel(const std::string& label, bool byPriority) const {
  auto tasks = taskView_->GetTasksByLabel(label);
  std::vector<TaskRepositoryDTO> tasksDTO;
  for (const auto& task : tasks){
    tasksDTO.push_back(DTOFromEntity(task));
  }
  if (byPriority){
    SortByPriority(tasksDTO);
  }
  return tasksDTO;
}

std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetTasksByName(const std::string& name, bool byPriority) const {
  auto tasks = taskView_->GetTasksByName(name);
  std::vector<TaskRepositoryDTO> tasksDTO;
  for (const auto& task : tasks){
    tasksDTO.push_back(DTOFromEntity(task));
  }
  if (byPriority){
    SortByPriority(tasksDTO);
  }
  return tasksDTO;
}
std::vector<TaskRepositoryDTO> TaskRepositoryClass::GetTasksByPriority(const Priority& priority) const {
  auto tasks = taskView_->GetTasksByPriority(priority);
  std::vector<TaskRepositoryDTO> tasksDTO;
  for (const auto& task : tasks){
    tasksDTO.push_back(DTOFromEntity(task));
  }
  return tasksDTO;
}

TaskRepositoryDTO TaskRepositoryClass::DTOFromEntity(const TaskEntity &entity) const {
  auto task = TaskRepositoryDTO::Create(entity.GetName(), entity.GetLabel(), entity.GetPriority(),
                            entity.GetDueDate(), entity.IsComplete(), entity.GetId(), entity.GetParentId());
  assert(task.has_value());

  return task.value();
}

std::optional<TaskEntity> TaskRepositoryClass::EntityFromDTO(const TaskRepositoryDTO &dto) {
  auto newTask = Task::Create(dto.GetName(), dto.GetLabel(), dto.GetPriority(), dto.GetDate());
  if (!newTask.has_value()){
    return std::nullopt;
  }
  return TaskEntity(newTask.value(), taskIDGenerate_.Generate());
}

void TaskRepositoryClass::SortByPriority(std::vector<TaskRepositoryDTO> &tasks) const {
  std::sort(tasks.begin(), tasks.end(),
           [](const TaskRepositoryDTO& first, const TaskRepositoryDTO& second) {
              return first.GetPriority() < second.GetPriority();
            }
            );
}