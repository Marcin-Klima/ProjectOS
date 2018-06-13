//
// Created by waxta on 23.05.18.
//

#include <random>
#include <algorithm>
#include "Worker.h"
#include "SyncRandomGenerator.h"

const std::string Worker::ASCIIModel[] = {  " o ",
									        "/|\\",
									        "/ \\"};

Worker::Worker() : Drawable(), workerThread(nullptr), hungerThread(nullptr),
                   plantation(nullptr), granary(nullptr), king(nullptr)
{
	modelHeight = 3;
	hunger = 100;
	working = false;
	activity = Activity::Wondering;
	foodPayload = 0;
	isAlive = true;
}

Worker::~Worker()
{
}

void Worker::Simulate()
{
	int time;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> dist(500, 2000);
	std::uniform_int_distribution<int> chanceDist(0, 100);
	time = dist(generator);

	while(working == true && isAlive == true)
	{
		if(hunger <= 20 && granary->GetCurrentCapacity() >= 10)
		{
			GoEat();
		}
		if(foodPayload != 0)
		{
			GoToGranary();
		}
		else
		{
			GoWorkOnPlantation();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
		if(isAlive == false)
		{
			activity = Activity::Dead;
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
	if(hungerThread != nullptr)
	{
		delete hungerThread;
		hungerThread = nullptr;
	}
}

void Worker::StartWorking()
{
	if(working == false && isAlive == true)
	{
		working = true;

		workerThread = new std::thread(&Worker::Simulate, this);
		if(workerThread->joinable())
		{
			workerThread->detach();
		}

		hungerThread = new std::thread(&Worker::HungerSimulationThread, this);
		if(hungerThread->joinable())
		{
			hungerThread->detach();
		}
	}
}

std::string Worker::GetActivity()
{
	switch(activity)
	{
		case Activity::Working:
			return "Working";
		case Activity::Wondering:
			return "Wondering";
		case Activity::Eating:
			return "Eating";
		case Activity::OnWayToLeader:
			return "Going to leader";
		case Activity::Waiting:
			return "Waiting";
		case Activity::WanderUp:
			return "Wander Up";
		case Activity::PuttingAwayFood:
			return "Putting Food Away";
		case Activity::Dead:
			return "Dead";
		case Activity::InQueue:
			return "In Queue";
		default:
			return "Unspecified";
	}
}

void Worker::HungerSimulationThread()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> dist(150, 600);
	int time;
	do
	{
		if(hunger > 0 && activity != Activity::Eating)
		{
			time = dist(generator);
			--hunger;
			std::this_thread::sleep_for(std::chrono::milliseconds(time));
		}
		else if(hunger == 0)
		{
			isAlive = false;
			StopWorking();
		}
	}while(isAlive == true && working == true);
	activity = Activity::Dead;
}

void Worker::GoWorkOnPlantation()
{
	unsigned int xPos, yPos;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<unsigned int> distribution(0, 4);
	std::uniform_int_distribution<unsigned int> foodPayloadDistribution(1, 3);

	activity = Activity::Waiting;
	do{
		xPos = distribution(generator);
		yPos = distribution(generator);
	}while(plantation->ReserveSpaceOnPlantation(xPos, yPos) != true);

	activity = Activity::Working;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	plantation->FreeSpaceOnPlantation(xPos, yPos);
	foodPayload = foodPayloadDistribution(generator);
}

void Worker::SetPlanatation(Plantation *plantation)
{
	this->plantation = plantation;
}

void Worker::SetGranary(Granary *granary)
{
	this->granary = granary;
}

void Worker::GoToGranary()
{
	bool putFoodCompleted;
	activity = Activity::WanderUp;
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	do
	{
		putFoodCompleted = granary->PutFood(foodPayload);
		if(putFoodCompleted == false)
		{
			activity = Activity::Waiting;
		}
	}while(putFoodCompleted == false);
	activity = Activity::PuttingAwayFood;
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	foodPayload = 0;
}

void Worker::GoEat()
{
	activity = Activity::WanderUp;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	activity = Activity::InQueue;
	king->FeedWorkers();
	activity = Activity::Eating;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	hunger = 100;

}

void Worker::SetKing(King *king)
{
	this->king = king;

}
