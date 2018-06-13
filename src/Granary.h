//
// Created by waxta on 23.05.18.
//

#pragma once
#include <string>
#include <mutex>
#include "Drawable.h"

class Granary : public Drawable
{
public:
	Granary();
	virtual ~Granary();
	virtual const std::string * getASCIIModel() { return ASCIIModel; }
	unsigned int GetCurrentCapacity() { return currentCapacity; }
	bool PutFood(unsigned int foodVolume);
	void TakeFood(unsigned int count);

private:
	static const std::string ASCIIModel[];
	const unsigned int maxCapacity = 100;
	unsigned int currentCapacity;
	std::mutex mutex;
};