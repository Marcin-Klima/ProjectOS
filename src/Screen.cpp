//
// Created by waxta on 23.05.18.
//

#include <ncurses.h>
#include "Screen.h"
#include "Granary.h"

Screen::Screen() : screenThread(nullptr), running(false), workers(nullptr),
                   granary(nullptr)
{
	initscr();
	getmaxyx(stdscr, ScreenYSize, ScreenXSize);
	curs_set(0);
	noecho();
}

Screen::~Screen()
{
	delete screenThread;
}

void Screen::StartRunning()
{
	running = true;
	screenThread = new std::thread(&Screen::Loop, this);
}

void Screen::Loop()
{
	do
	{
		DrawGranary();
		DrawWorkers();


		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}while(running == true);
}

void Screen::Close()
{
	running = false;
	screenThread->join();

	endwin();
}

void Screen::AddDrawable(Drawable &drawable)
{
	drawables.push_back(&drawable);

}

void Screen::SetWorkersVector(std::vector<Worker> *workers)
{
	this->workers = workers;
}

void Screen::DrawWorkers()
{
	static const unsigned int workersFrameXPos = 2;
	static const unsigned int workersFrameYPos = 30;

	move(workersFrameYPos, workersFrameXPos);

	unsigned int currentXPos = workersFrameXPos;
	unsigned int currentYPos = workersFrameYPos;
	for(int i = 0; i < workers->size(); ++i)
	{
		mvprintw(currentYPos - 2, currentXPos, "Hunger: ");
		int hungerLevel = workers->at(i).GetHunger();
		printw("   ");
		mvprintw(currentYPos - 2, currentXPos + 8, std::to_string(hungerLevel).c_str());
		refresh();

		for(int j = 0; j < workers->at(i).GetModelHeight(); ++j)
		{
			mvprintw(currentYPos, currentXPos, workers->at(i).GetASCIIModel()[j].c_str());
			++currentYPos;
		}
		if(currentXPos + 15 > ScreenXSize)
		{
			currentXPos = workersFrameXPos;
			currentYPos += 8;
		}
		else
		{
			currentXPos += 15;
		}
		currentYPos -= 3;
	}
}

void Screen::SetGranary(Granary *granary)
{
	this->granary = granary;
}

void Screen::DrawGranary()
{
	static const unsigned int granaryXPos = 2;
	static const unsigned int granaryYPos = 17;
	int currentYPos = granaryYPos;

	for(int i = 0; i < granary->GetModelHeight(); ++i)
	{
		mvprintw(currentYPos, granaryXPos, granary->getASCIIModel()[i].c_str());
		++currentYPos;

	}
	refresh();
}
