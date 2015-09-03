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

#include <libgen.h>
#include <stdlib.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <functional>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <mesos/resources.hpp>
#include <mesos/scheduler.hpp>
#include "first_framework.hpp"

using namespace mesos;

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::queue;
using std::map;

using mesos::Resources;

MesosSchedulerDriver* schedulerDriver;

static void SIGINTHandler();

class first_framework : public Scheduler
{
public:
	first_framework(const ExecutorInfo& tmp)
		: anofun(tmp),
		  tasksLaunched(0),
		  tasksFinished(0),
		  answer(0) {}

	virtual ~first_framework() {}

	virtual void registered(SchedulerDriver* driver,
							const FrameworkID& framworkID,
							const MasterInfo& masterInfo)
	{
		cout << "Scheduler Registered with id " << framworkID.value() << endl; //->get_value() << endl;
	}

	virtual void reregistered(SchedulerDriver*, const MasterInfo& masterInfo) 
	{
		cout << "Scheduler re-registered!" << endl;
	}

	virtual void disconnected(SchedulerDriver* driver) {}

	virtual void resourceOffers(SchedulerDriver* driver,
								const vector<Offer>& offers)
	{
		cout << "Scheduler received offers " << offers.size() << endl;
	}

	virtual void offerRescinded(SchedulerDriver* driver, const OfferID& offerId) {}

	virtual void statusUpdate(SchedulerDriver* driver, const TaskStatus& status) 
	{
		cout << "Status update: task " << endl;
	}

	virtual void frameworkMessage(SchedulerDriver* driver,
								  const ExecutorID& executorId,
								  const SlaveID& slaveId,
								  const string& data)
	{
		cout << data << endl;
	}

	virtual void slaveLost(SchedulerDriver* driver, const SlaveID& sid) {}

	virtual void executorLost(SchedulerDriver* driver,
							  const ExecutorID& executorID,
							  const SlaveID& slaveID,
							  int status)
	{
		cout << "Executor " << executorID.value() << " lost!" << endl;
	}

	virtual void error(SchedulerDriver* driver, const string& message)
	{
		cout << message << endl;
	}

private:
	const ExecutorInfo anofun;
	size_t tasksLaunched;
	size_t tasksFinished;
	size_t answer;
};

#define shift argc--,argv++
int main(int argc, char** argv)
{
  	string master;
  	shift;
  	while (true) {
  	  string s = argc>0 ? argv[0] : "--help";
  	  if (argc > 1 && s == "--master") {
  	    master = argv[1];
  	    shift; shift;
  	  } else {
  	    break;
  	  }
  	}
	
  	if (master.length() == 0) {
  	  printf("Usage: SomeScheduler --master <ip>:<port>\n");
  	  exit(1);
  	}

	cout << "Starting my first_framework on Mesos with master " << argv[0] << endl;

	ExecutorInfo ff;
	ff.mutable_executor_id()->set_value("random value acceptable");
	ff.mutable_command()->set_value("random value command");
	ff.set_name("random name");
	ff.set_source("cpp");

	first_framework scheduler(ff);

	FrameworkInfo framework;
	framework.set_user("gilbert");
	framework.set_name("first_framework(c++)");
	framework.set_principal("first_framework-cpp");

	schedulerDriver = new MesosSchedulerDriver(&scheduler, framework, master);

	int status = schedulerDriver->run() == DRIVER_STOPPED ? 0 : 1;

	return 0;
}
















