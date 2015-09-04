/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#include <stout/lambda.hpp>
#include <stout/numify.hpp>
#include <stout/stringify.hpp>
#include <mesos/executor.hpp>
#include "first_framework.hpp"

using namespace mesos;

using std::cout;
using std::endl;
using std::string;

static void runTask(ExecutorDriver* driver, const TaskInfo& task)
{
  cout << "running nothing now" << endl;

  TaskStatus status;
  status.mutable_task_id()->MergeFrom(task.task_id());
  status.set_state(TASK_FINISHED);
  driver->sendStatusUpdate(status);
}


void* start(void* arg)
{
  lambda::function<void(void)>* thunk = (lambda::function<void(void)>*) arg;
  (*thunk)();
  delete thunk;
  return NULL;
}

class MathExecutor : public Executor
{
  public:
    virtual ~MathExecutor() {}

    virtual void registered(ExecutorDriver* driver,
                            const ExecutorInfo& executorInfo,
                            const FrameworkInfo& frameworkInfo,
                            const SlaveInfo& slaveInfo)
    {
      cout << "Registered MathExecutor on " << slaveInfo.hostname() << endl;
    }

    virtual void reregistered(ExecutorDriver* driver,
                              const SlaveInfo& slaveInfo)
    {
      cout << "Re-registered MathExecutor on " << slaveInfo.hostname() << endl;
    }

    virtual void disconnected(ExecutorDriver* driver) {}


    virtual void launchTask(ExecutorDriver* driver, const TaskInfo& task)
    {
      cout << "Starting task " << task.task_id().value() << endl;

      lambda::function<void(void)>* thunk =
        new lambda::function<void(void)>(lambda::bind(&runTask, driver, task));

      pthread_t pthread;
      if (pthread_create(&pthread, NULL, &start, thunk) != 0) {
        TaskStatus status;
        status.mutable_task_id()->MergeFrom(task.task_id());
        status.set_state(TASK_FAILED);

        driver->sendStatusUpdate(status);
      } else {
        pthread_detach(pthread);

        TaskStatus status;
        status.mutable_task_id()->MergeFrom(task.task_id());
        status.set_state(TASK_RUNNING);

        driver->sendStatusUpdate(status);
      }
    }

  virtual void killTask(ExecutorDriver* driver, const TaskID& taskId) {}
  virtual void frameworkMessage(ExecutorDriver* driver, const string& data) {}
  virtual void shutdown(ExecutorDriver* driver) {}
  virtual void error(ExecutorDriver* driver, const string& message) {}
};


int main(int argc, char** argv)
{
  MathExecutor executor;
  MesosExecutorDriver driver(&executor);
  return driver.run() == DRIVER_STOPPED ? 0 : 1;
}
