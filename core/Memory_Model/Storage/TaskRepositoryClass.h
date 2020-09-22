//
// Created by R2D2 on 31.07.2020.
//

#ifndef TASKMANAGER_SRC_TASKREPOSITORY_H_
#define TASKMANAGER_SRC_TASKREPOSITORY_H_
#include "TaskRepository.h"

 class TaskRepositoryClass
     : public TaskRepository {
 public:
  TaskRepositoryClass(std::unique_ptr<TaskView> view, std::unique_ptr<TaskStorage> storage);

 public:
  const std::unique_ptr<TaskView>&                          GetTaskView() const override;
  const std::unique_ptr<TaskStorage>&                       GetTaskStorage() const override;

  AddTaskResult                                             AddTask(const TaskDTO& task) override;
  AddTaskResult                                             AddSubtask(const TaskID& rootTaskID, const TaskDTO& subtask) override;
  bool                                                      RemoveTask(const TaskID& id) override;
  bool                                                      PostponeTask(const TaskID& id, const Date& date) override;

  bool                                                      SaveToFile(const std::string& fileName) override;
  bool                                                      LoadFromFile(const std::string& fileName) override;

 private:
  std::unique_ptr<TaskView>      taskView_;
  std::unique_ptr<TaskStorage>   taskStorage_;
};

#endif //TASKMANAGER_SRC_TASKREPOSITORY_H_
