//
// Created by waxta on 23.05.18.
//

#pragma once

#include <string>
#include <thread>
#include "Drawable.h"
#include "Plantation.h"
#include "Granary.h"
#include "King.h"


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
	std::string GetActivity();
	void SetPlanatation(Plantation * plantation);
	void SetGranary(Granary * granary);
	bool isAlive;
	volatile bool working;
	void SetKing(King * king);

	enum class Activity
	{
		Working,
		Eating,
		OnWayToLeader,
		Wondering,
		Waiting,
		WanderUp,
		PuttingAwayFood,
		InQueue,
		Dead
	};
	Activity activity;

private:
	std::thread * workerThread;
	std::thread * hungerThread;
	Plantation * plantation;
	Granary * granary;
	King * king;
	void Simulate();
	void HungerSimulationThread();
	void GoWorkOnPlantation();
	void GoToGranary();
	void GoEat();
	unsigned short hunger;
	unsigned int foodPayload;
};