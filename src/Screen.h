//
// Created by waxta on 23.05.18.
//

#pragma once

#include <thread>

class Screen
{
public:
	Screen();
	void Initialize();
	void Display();
	void Close();
	~Screen();

private:
	std::thread * screenThread;
	unsigned int XSize, YSize;
	void Loop();
	bool running;
};


