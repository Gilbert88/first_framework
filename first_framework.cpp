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
		  anser(0) {}

	virtual ~first_framework() {}

	virtual void registered(SchedulerDrive*,
							const FrameworkID&,
							const MasterInfo&)
	{
		cout << "registered!" << endl;
	}

	virtual void reregistered(SchedulerDrive*, const MasterInfo& masterInfo) {}

	virtual void disconnected(SchedulerDrive* driver) {}

	virtual void resourceOffers(SchedulerDrive* driver,
								const Offer& offers)
	{

	}

	virtual void offerRescinded(SchedulerDrive* driver, const OfferID& offerId) {}

	virtual void statusUpdate(SchedulerDrive* driver, const TaskStatus& status) {}

	virtual void frameworkMsssage(SchedulerDrive* driver,
								  const ExecutorID& executorId,
								  const SlaveID& slaveId,
								  const string& data)
	{
		cout << data << endl;
	}

	virtual void slaveLost(SchedulerDrive* driver, const SlaveID& sid) {}

	virtual void executorList(SchedulerDrive* driver,
							  const ExecutorID&)
};
















