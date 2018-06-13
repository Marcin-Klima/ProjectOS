//
// Created by waxta on 29.05.18.
//

#include <random>
#include "Plantation.h"

std::string Plantation::ASCIIModel[] = {    "~~ ~~ ~~ ~~ ~~",
											"~~ ~~ ~~ ~~ ~~",
											"~~ ~~ ~~ ~~ ~~",
											"~~ ~~ ~~ ~~ ~~",
											"~~ ~~ ~~ ~~ ~~"};

Plantation::~Plantation()
{
	if(!mutex.try_lock())
	{
		mutex.unlock();
	}
	if(natureThread->joinable())
	{
		natureThread->join();
	}
	delete natureThread;
}

Plantation::Plantation() : working(true)
{
	modelHeight = 5;
	workersOnPlantation = 0;
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			occupationArray[i][j] = false;
		}
	}
}

void Plantation::StartSimulation()
{
	working = true;
	natureThread = new std::thread(&Plantation::Simulate, this);
}

void Plantation::Simulate()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> timeDistribution(500, 1000);
	std::uniform_int_distribution<int> plantationCoordinateDistribution(0, 4);
	int widthCoord, heightCoord;
	int timeInterval;
	do
	{
		widthCoord = plantationCoordinateDistribution(generator);
		heightCoord = plantationCoordinateDistribution(generator);
		std::string current = ASCIIModel[heightCoord].substr(widthCoord * 3, 2);
		if(current == "~~")
		{
			ASCIIModel[heightCoord].replace(3 * widthCoord, 2, "||");
			timeInterval = timeDistribution(generator);
		}
		else
		{
			timeInterval = 0;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(timeInterval));
	}while(working);
}

void Plantation::StopSimulation()
{
	working = false;
	if(natureThread->joinable())
	{
		natureThread->join();
	}
}

bool Plantation::ReserveSpaceOnPlantation(unsigned int xPos, unsigned int yPos)
{
	mutex.lock();

	if(occupationArray[yPos][xPos] == false && ASCIIModel[yPos].substr(3 * xPos, 2) == "||")
	{
		occupationArray[yPos][xPos] = true;
		++workersOnPlantation;
		mutex.unlock();
		return true;
	}
	else
	{
		mutex.unlock();
		return false;
	}

}

void Plantation::FreeSpaceOnPlantation(unsigned int xPos, unsigned int yPos)
{
	occupationArray[yPos][xPos] = false;
	ASCIIModel[yPos].replace(3 * xPos, 2, "~~");
	--workersOnPlantation;
}
