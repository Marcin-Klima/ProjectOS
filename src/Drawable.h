// Created by waxta on 29.05.18.
//

#pragma once


#include <string>

class Drawable
{
public:
	Drawable();
	unsigned int GetModelHeight() const { return modelHeight; }

	virtual ~Drawable();

protected:
	unsigned int modelHeight;
};


