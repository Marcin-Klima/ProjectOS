//
// Created by waxta on 29.05.18.
//

#pragma once


#include <string>

class Drawable
{
public:
	Drawable();
	unsigned int GetXPositon() const  { return xPosition; }
	unsigned int GetYPosition() const { return yPosition; }
	unsigned int GetModelHeight() const { return modelHeight; }
	void SetPosition(unsigned int xPos, unsigned int yPos);
	~Drawable();

protected:
	unsigned int xPosition;
	unsigned int yPosition;
	unsigned int modelHeight;
};


