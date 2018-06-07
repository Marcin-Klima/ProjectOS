//
// Created by waxta on 22.05.18.
//

#include <iostream>
#include "MainApplication.h"

MainApplication::MainApplication() : running(false), screen()
{
	for(int i = 0; i < 10; ++i)
	{
		workers.push_back(Worker());
	}

	screen.SetWorkersVector(&workers);
	screen.SetGranary(&granary);

	granary.SetPosition(2, 15);
	screen.AddDrawable(granary);
}

void MainApplication::Start()
{
	running = true;
	screen.StartRunning();
	for(int i = 0; i < workers.size(); ++i)
	{
		workers[i].StartWorking();
	}
	for(int i = 0; i < workers.size(); ++i)
	{
		workers[i].StartWorking();
	}
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
	userInputThread->join();
}

void MainApplication::Stop()
{
	for(int i = 0; i < workers.size(); ++i)
	{
		workers[i].StopWorking();
	}

	screen.Close();
	workers.clear();
}
