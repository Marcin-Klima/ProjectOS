//
// Created by waxta on 12.06.18.
//

#include <thread>
#include "King.h"

std::string King::ASCIIModel[] = { "KING" };

King::King()
{
	workersInQueue = 0;
	modelHeight = 1;
}

void King::FeedWorkers()
{
	++workersInQueue;
	mutex.lock();
	{
		while(granary->GetCurrentCapacity() < 10)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		granary->TakeFood(10);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	mutex.unlock();
	--workersInQueue;
}

void King::SetGranary(Granary *granary)
{
	this->granary = granary;

}
