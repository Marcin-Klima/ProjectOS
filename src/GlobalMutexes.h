//
// Created by waxta on 17.06.18.
//

#pragma once


#include <mutex>

class GlobalMutexes
{
public:
	static std::mutex mutex_workersVector;
};


