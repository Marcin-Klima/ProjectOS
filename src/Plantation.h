//
// Created by waxta on 29.05.18.
//

#pragma once


#include "Drawable.h"
#include <string>

class Plantation : public Drawable
{
public:
	virtual const std::string * GetASCIIModel() { return ASCIIModel; }
	static std::string ASCIIModel[];
	virtual ~Plantation();

private:
	const unsigned int width = 5;
	const unsigned int height = 5;
	bool occupationArray[5][5] = {false};
};