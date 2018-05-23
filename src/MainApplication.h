//
// Created by waxta on 22.05.18.
//

#pragma once


#include "Screen.h"

class MainApplication
{
public:
	MainApplication();
	~MainApplication();

	void Start();
	void WaitForUserInput();

private:
	bool running;
	Screen screen;
	std::thread * userInputThread;

	void UserInput();
};