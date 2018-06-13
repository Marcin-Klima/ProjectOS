//
// Created by waxta on 29.05.18.
//

#pragma once


#include "Drawable.h"
#include <string>
#include <thread>
#include <mutex>

class Plantation : public Drawable
{
public:
	Plantation();
	virtual const std::string * GetASCIIModel() { return ASCIIModel; }
	static std::string ASCIIModel[];
	~Plantation();
	void StartSimulation();
	void StopSimulation();
	unsigned int GetWorkersOnPlantation() { return workersOnPlantation; }
	bool ReserveSpaceOnPlantation(unsigned int xPos, unsigned int yPos);
	void FreeSpaceOnPlantation(unsigned int  xPos, unsigned int yPos);

private:
	std::mutex mutex;
	volatile bool working;
	std::thread * natureThread;
	bool occupationArray[5][5];
	unsigned int workersOnPlantation;
	void Simulate();
};