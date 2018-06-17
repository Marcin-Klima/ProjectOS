//
// Created by waxta on 23.05.18.
//

#include "Granary.h"

const std::string Granary::ASCIIModel[] = {     "   /\\",
							                    "  /  \\",
							                    " /    \\",
								                "/      \\",
								                "|      |",
								                "|      |",
								                "|______|"};

Granary::Granary()
{
	modelHeight = 7;
	currentCapacity = 0;
}

Granary::~Granary()
{

}

bool Granary::PutFood(unsigned int foodVolume)
{
	mutex.lock();

	if(currentCapacity + foodVolume < maxCapacity)
	{
		currentCapacity += foodVolume;
		mutex.unlock();
		return true;
	}
	else
	{
		mutex.unlock();
		return false;
	}
}

void Granary::TakeFood(unsigned int count)
{
	mutex.lock();
	currentCapacity -= count;
	mutex.unlock();
}

