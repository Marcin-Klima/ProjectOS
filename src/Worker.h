//
// Created by waxta on 23.05.18.
//

#pragma once

#include <string>
#include <thread>
#include "Drawable.h"

class Worker : public Drawable
{
public:
	Worker();
	virtual ~Worker();

	static const std::string ASCIIModel[];
	virtual const std::string * GetASCIIModel() { return ASCIIModel; }
	unsigned short GetHunger() { return hunger; }
	void StartWorking();
	void StopWorking();

private:
	std::thread * workerThread;
	void Simulate();
	unsigned short hunger;
	volatile bool working;
};