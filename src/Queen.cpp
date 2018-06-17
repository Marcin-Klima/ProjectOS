//
// Created by waxta on 11.06.18.
//

#include <random>
#include "Queen.h"
#include "GlobalMutexes.h"

std::string Queen::ASCIIModel[] = { "QUEEN" };

Queen::Queen() : queenThread(nullptr), workers(nullptr)
{
	modelHeight = 1;
	working = false;
	maxWorkers = 16;
}

Queen::~Queen()
{
	delete queenThread;
}

void Queen::StartSimulation()
{
	working = true;
	queenThread = new std::thread(&Queen::Simulation, this);
}

void Queen::Simulation()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> dist(500, 2000);

	const int timeInterval = 4000;
	int timePassed;
	int timeBetweenNewWorkers;
	do
	{
		timeBetweenNewWorkers = dist(generator);
		newWorkerProgressPercentage = 0;
		timePassed = 0;
		do
		{
			newWorkerProgressPercentage = timePassed * 100 / timeInterval;
			timePassed += 50;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}while(timePassed <= timeInterval && working == true);

		GlobalMutexes::mutex_workersVector.lock();
		while(workers->size() >= maxWorkers && working == true)
		{
			GlobalMutexes::mutex_workersVector.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			GlobalMutexes::mutex_workersVector.lock();
		}
		workers->push_back(Worker());
		workers->at(workers->size() - 1).SetGranary(granary);
		workers->at(workers->size() - 1).SetPlanatation(plantation);
		workers->at(workers->size() - 1).SetKing(king);
		workers->at(workers->size() - 1).StartWorking();
		GlobalMutexes::mutex_workersVector.unlock();

		std::this_thread::sleep_for(std::chrono::milliseconds(timeBetweenNewWorkers));
	}while(working == true);
}

void Queen::StopSimulation()
{
	working = false;
	if(queenThread->joinable())
	{
		queenThread->join();
	}
}

void Queen::SetWorkersVector(std::vector<Worker> *workers)
{
	this->workers = workers;
}

void Queen::SetGranary(Granary *granary)
{
	this->granary = granary;
}

void Queen::SetPlanation(Plantation *plantation)
{
	this->plantation = plantation;
}

void Queen::SetKing(King *king)
{
	this->king = king;
}
