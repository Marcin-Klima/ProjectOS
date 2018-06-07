//
// Created by waxta on 01.06.18.
//

#include <random>
#include "SyncRandomGenerator.h"

std::mutex SyncRandomGenerator::mutex;

int SyncRandomGenerator::GenerateRandomNumber(int min, int max)
{
	mutex.lock();

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> dist(min, max);

	int value = dist(generator);

	mutex.unlock();

	return value;
}
