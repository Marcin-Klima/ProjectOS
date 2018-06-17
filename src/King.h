//
// Created by waxta on 12.06.18.
//

#pragma once


#include <string>
#include "Drawable.h"
#include "Granary.h"

class King : public Drawable
{
public:
	King();
	static std::string ASCIIModel[];
	virtual const std::string * GetASCIIModel() { return ASCIIModel; }
	void FeedWorkers();
	void SetGranary(Granary * granary);
	unsigned int GetWorkersInQueue() { return workersInQueue; }

private:
	Granary *granary;
	std::mutex kingMutex;
	unsigned int workersInQueue;
};


