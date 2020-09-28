//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskRepository.h"
#include "TaskViewClass.h"
#include "TaskStorageClass.h"

 class TaskRepositoryClass
     : public TaskRepository {
 public:
  TaskRepositoryClass(std::unique_ptr<TaskView> view, std::unique_ptr<TaskStorage> storage);

 public:
  void                                ResetRepository() override;

  AddTaskResult                       AddTask(const TaskRepositoryDTO& task) override;
  AddTaskResult                       AddSubtask(const TaskID& rootTaskID, const TaskRepositoryDTO& subtask) override;
  bool                                RemoveTask(const TaskID& id) override;
  bool                                PostponeTask(const TaskID& id, const Date& date) override;
  bool                                SetTaskComplete(const TaskID& id) override;

  std::optional<TaskRepositoryDTO>    GetTask(const TaskID& id) const override;
  std::vector<TaskRepositoryDTO>      GetSubtask(const TaskID& id) const override;
  std::vector<TaskRepositoryDTO>      GetTasks(bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTodayTasks(bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetWeekTasks(bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTasksByLabel(const std::string& label, bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTasksByName(const std::string& name, bool byPriority) const override;
  std::vector<TaskRepositoryDTO>      GetTasksByPriority(const Priority& priority) const override;

 private:
   TaskRepositoryDTO                  DTOFromEntity(const TaskEntity& entity) const;
   std::optional<TaskEntity>          EntityFromDTO(const TaskRepositoryDTO& dto);
   void                               SortByPriority(const std::vector<TaskRepositoryDTO>& tasks) const;

 private:
  std::unique_ptr<TaskView>           taskView_;
  std::unique_ptr<TaskStorage>        taskStorage_;
  TaskIDGenerate                      taskIDGenerate_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
