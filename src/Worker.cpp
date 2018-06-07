//
// Created by waxta on 23.05.18.
//

#include "Worker.h"
#include "SyncRandomGenerator.h"

const std::string Worker::ASCIIModel[] = {  " o ",
									        "/|\\",
									        "/ \\"};

Worker::Worker() : Drawable(), workerThread(nullptr)
{
	modelHeight = 3;
	hunger = 100;
	working = false;
}

Worker::~Worker()
{
}

void Worker::Simulate()
{
	int time;

	while(working == true)
	{
		if(hunger > 0)
		{
			time = SyncRandomGenerator::GenerateRandomNumber(150, 2000);
			--hunger;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
		}
	}
}

void Worker::StopWorking()
{
	working = false;
	if(workerThread != nullptr)
	{
		delete workerThread;
		workerThread = nullptr;
	}
}

void Worker::StartWorking()
{
	working = true;
	workerThread = new std::thread(&Worker::Simulate, this);
	if(workerThread->joinable())
	{
		workerThread->detach();
	}
}
