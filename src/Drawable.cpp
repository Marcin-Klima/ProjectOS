//
// Created by waxta on 29.05.18.
//

#include "Drawable.h"

Drawable::Drawable()
{
	xPosition = 0;
	yPosition = 0;
}

void Drawable::SetPosition(unsigned int xPos, unsigned int yPos)
{
	xPosition = xPos;
	yPosition = yPos;
}

Drawable::~Drawable()
{

}
