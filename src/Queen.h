//
// Created by waxta on 11.06.18.
//

#pragma once

#include <string>
#include <thread>
#include "Drawable.h"
#include "Worker.h"
#include "King.h"

class Queen : public Drawable
{
public:
	Queen();
	~Queen();
	virtual const std::string * GetASCIIModel() { return ASCIIModel; }
	static std::string ASCIIModel[];
	void StartSimulation();
	void StopSimulation();
	unsigned int GetNewWorkerProgressPercentage() { return newWorkerProgressPercentage; }
	void SetWorkersVector(std::vector<Worker> * workers);
	void SetPlanation(Plantation * plantation);
	void SetGranary(Granary * granary);
	void SetKing(King * king);

private:
	std::thread * queenThread;
	void Simulation();
	volatile bool working;
	unsigned int newWorkerProgressPercentage;
	std::vector<Worker> * workers;
	Plantation * plantation;
	Granary * granary;
	King * king;
	unsigned int maxWorkers;
};


