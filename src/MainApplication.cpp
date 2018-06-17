//
// Created by waxta on 22.05.18.
//

#include <iostream>
#include "MainApplication.h"
#include "GlobalMutexes.h"

MainApplication::MainApplication() : running(false), screen(), userInputThread(nullptr)
{
	/*for(int i = 0; i < 10; ++i)
	{
		workers.push_back(Worker());
		workers[i].SetPlanatation(&plantation);
		workers[i].SetGranary(&granary);
	}
*/
	queen.SetWorkersVector(&workers);
	queen.SetGranary(&granary);
	queen.SetPlanation(&plantation);
	queen.SetKing(&king);

	king.SetGranary(&granary);

	screen.SetWorkersVector(&workers);
	screen.SetGranary(&granary);
	screen.SetPlantation(&plantation);
	screen.SetQueen(&queen);
	screen.SetKing(&king);
}

void MainApplication::Start()
{
	running = true;
	screen.StartRunning();
	queen.StartSimulation();
	plantation.StartSimulation();

	GlobalMutexes::mutex_workersVector.lock();
	for(int i = 0; i < 10; ++i)
	{
		workers.push_back(Worker());
		workers[i].SetPlanatation(&plantation);
		workers[i].SetGranary(&granary);
		workers[i].SetKing(&king);
	}
	for(int i = 0; i < workers.size(); ++i)
	{
		workers[i].StartWorking();
	}
	GlobalMutexes::mutex_workersVector.unlock();
}

MainApplication::~MainApplication()
{
	delete userInputThread;
}


void MainApplication::UserInput()
{
	while(running == true)
	{
		if(std::cin.get() == 'q')
		{
			running = false;
		}
	}
}

void MainApplication::WaitForUserInput()
{
	userInputThread = new std::thread(&MainApplication::UserInput, this);
	if(userInputThread->joinable())
	{
		userInputThread->join();
	}
}

void MainApplication::Stop()
{
	queen.StopSimulation();
	for(int i = 0; i < workers.size(); ++i)
	{
		workers[i].StopWorking();
	}
	plantation.StopSimulation();

	screen.Close();

	GlobalMutexes::mutex_workersVector.lock();
	workers.clear();
	GlobalMutexes::mutex_workersVector.unlock();
}