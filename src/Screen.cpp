//
// Created by waxta on 23.05.18.
//

#include <ncurses.h>
#include "Screen.h"
#include "Granary.h"

Screen::Screen() : screenThread(nullptr), working(false), workers(nullptr),
                   granary(nullptr), plantation(nullptr)
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
	working = true;
	screenThread = new std::thread(&Screen::Loop, this);
}

void Screen::Loop()
{
	do
	{
		DeleteDeadWorkers();

		std::string activerWorkers = "Active Workers: ";
		activerWorkers.erase(16);
		activerWorkers += std::to_string(workers->size());
		mvprintw(0, ScreenXSize / 2 - activerWorkers.length() / 2, activerWorkers.c_str());
		DrawPlantation();
		DrawGranary();
		DrawWorkers();
		DrawQueen();
		DrawKing();

		refresh();
		clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}while(working == true);
}

void Screen::Close()
{
	working = false;
	screenThread->join();

	endwin();
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
		mvprintw(currentYPos - 1, currentXPos, "                   ");
		mvprintw(currentYPos - 1, currentXPos, workers->at(i).GetActivity().c_str());

		for(int j = 0; j < workers->at(i).GetModelHeight(); ++j)
		{
			mvprintw(currentYPos, currentXPos, workers->at(i).GetASCIIModel()[j].c_str());
			++currentYPos;
		}
		if(currentXPos + 33 > ScreenXSize)
		{
			currentXPos = workersFrameXPos;
			currentYPos += 8;
		}
		else
		{
			currentXPos += 19;
		}
		currentYPos -= 3;
	}
}


void Screen::DrawGranary()
{
	static const unsigned int granaryXPos = 2;
	static const unsigned int granaryYPos = 17;
	int currentYPos = granaryYPos;

	mvprintw(currentYPos - 2, granaryXPos, "Capacity: ");
	mvprintw(currentYPos - 2, granaryXPos + 10, "   ");
	mvprintw(currentYPos - 2, granaryXPos + 10, std::to_string(granary->GetCurrentCapacity()).c_str());
	mvprintw(currentYPos - 2, granaryXPos + 13, "/ 100");

	for(int i = 0; i < granary->GetModelHeight(); ++i)
	{
		mvprintw(currentYPos, granaryXPos, granary->getASCIIModel()[i].c_str());
		++currentYPos;

	}
	refresh();
}

void Screen::DrawPlantation()
{
	static const unsigned int xPos = ScreenXSize / 2 - 7;
	static const unsigned int yPos = 10;

	unsigned int currentYPos = yPos;
	for(int i = 0; i < plantation->GetModelHeight(); ++i)
	{
		mvprintw(yPos - 2, xPos, "Workers: ");
		mvprintw(yPos - 2, xPos + 10, "  ");
		mvprintw(yPos - 2, xPos + 10, std::to_string(plantation->GetWorkersOnPlantation()).c_str());
		mvprintw(yPos - 2, xPos + 12, "/25");
		mvprintw(currentYPos, xPos, plantation->GetASCIIModel()[i].c_str());
		++currentYPos;
	}
}

void Screen::DeleteDeadWorkers()
{
	for(unsigned int i = 0; i < workers->size(); ++i)
	{
		if(workers->at(i).isAlive == false)
		{
			deadWorkers.push_back(i);
		}
	}
	for(int i = 0; i < deadWorkers.size(); ++i)
	{
		if(workers->at(deadWorkers[i]).working == true)
		{
			workers->at(deadWorkers[i]).StopWorking();
		}
		workers->erase(workers->begin() + deadWorkers[i]);
	}
	deadWorkers.clear();
}

void Screen::DrawQueen()
{
	static const unsigned int xPos = ScreenXSize - 23;
	unsigned int yPos = 5;
	mvprintw(yPos - 2, xPos, "New worker: ");
	mvprintw(yPos - 2, xPos + 12, "   ");
	mvprintw(yPos - 2, xPos + 12, std::to_string(queen->GetNewWorkerProgressPercentage()).c_str());
	for(int i = 0; i < queen->GetModelHeight(); ++i)
	{
		mvprintw(yPos, xPos, queen->GetASCIIModel()[i].c_str());
		++yPos;
	}
}

void Screen::SetQueen(Queen *queen)
{
	this->queen = queen;
}

void Screen::SetGranary(Granary *granary)
{
	this->granary = granary;
}

void Screen::SetPlantation(Plantation *plantation)
{
	this->plantation = plantation;
}

void Screen::SetKing(King *king)
{
	this->king = king;
}

void Screen::DrawKing()
{
	for(int i = 0; i < king->GetModelHeight(); ++i)
	{
		mvprintw(4, 4, king->GetASCIIModel()[i].c_str());
	}
	mvprintw(5, 4, "Workers in queue: ");
	mvprintw(5, 22, "   ");
	mvprintw(5, 22, std::to_string(king->GetWorkersInQueue()).c_str());
}
