//
// Created by waxta on 22.05.18.
//

#include <iostream>
#include "MainApplication.h"

MainApplication::MainApplication() : running(false)
{

}

MainApplication::~MainApplication()
{
	screen.Close();
	delete userInputThread;
}

void MainApplication::Start()
{
	screen.Initialize();
	running = true;
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