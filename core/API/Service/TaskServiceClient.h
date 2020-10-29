//
// Created by valeriisudakov on 29.10.20.
//

#ifndef TASKMANAGER_CORE_API_SERVICE_TASKSERVICECLIENT_H_
#define TASKMANAGER_CORE_API_SERVICE_TASKSERVICECLIENT_H_
#include "TaskService.h"
#include "TaskServiceTransport.pb.h"
#include "TaskServiceTransport.grpc.pb.h"

class TaskServiceClient : public TaskService {
 public:
  TaskServiceClient(std::unique_ptr<transport::TaskService::Stub> server_request)
  : serverRequest_(std::move(server_request)) {  }

 public:
  AddTaskResult                   AddTask(const TaskServiceDTO &task) override;
  AddTaskResult                   AddSubtask(const TaskID &rootTaskID, const TaskServiceDTO &subtask) override;
  bool                            Load(const std::string &filename) override;
  bool                            Save(const std::string &filename) override;
  bool                            RemoveTask(const TaskID &ID) override;
  bool                            PostponeTask(const TaskID &ID, const Date &date) override;
  bool                            SetTaskComplete(const TaskID &ID) override;

 public:
  std::optional<TaskServiceDTO>   GetTask(const TaskID &id) const override;
  std::vector<TaskServiceDTO>     GetSubtask(const TaskID &id) const override;
  std::vector<TaskServiceDTO>     GetTasks(bool byPriority) const override;
  std::vector<TaskServiceDTO>     GetTodayTasks(bool byPriority) const override;
  std::vector<TaskServiceDTO>     GetWeekTasks(bool byPriority) const override;
  std::vector<TaskServiceDTO>     GetTasksByLabel(const std::string &label, bool byPriority) const override;
  std::vector<TaskServiceDTO>     GetTasksByName(const std::string &name, bool byPriority) const override;
  std::vector<TaskServiceDTO>     GetTasksByPriority(const Priority &priority) const override;
 private:
  std::unique_ptr<transport::TaskService::Stub> serverRequest_;
};

#endif //TASKMANAGER_CORE_API_SERVICE_TASKSERVICECLIENT_H_
