//
// Created by waxta on 22.05.18.
//

#pragma once


#include "Screen.h"
#include "Granary.h"
#include "Worker.h"

class MainApplication
{
public:
	MainApplication();
	~MainApplication();

	void Start();
	void WaitForUserInput();
	void Stop();

private:
	bool running;
	std::thread * userInputThread;

	Screen screen;
	Granary granary;

	std::vector<Worker> workers;

	void UserInput();
};