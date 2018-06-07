//
// Created by waxta on 23.05.18.
//

#pragma once
#include <string>
#include "Drawable.h"

class Granary : public Drawable
{
public:
	Granary();
	virtual ~Granary();

	virtual const std::string * getASCIIModel() { return ASCIIModel; }

private:
	static const std::string ASCIIModel[];
};