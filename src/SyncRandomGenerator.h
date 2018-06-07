//
// Created by waxta on 01.06.18.
//

#pragma once


#include <mutex>

class SyncRandomGenerator
{
public:
	static int GenerateRandomNumber(int min, int max);

private:
	static std::mutex mutex;
};


