//
// Created by waxta on 23.05.18.
//

#include <ncurses.h>
#include "Screen.h"

Screen::Screen() : screenThread(nullptr), running(false)
{
}

Screen::~Screen()
{
	delete screenThread;
}

void Screen::Display()
{
	initscr();
	getmaxyx(stdscr, YSize, XSize);

	std::string someTestText = "Hello World";
	move(YSize / 2, (XSize / 2) - (someTestText.length() / 2));
	printw(someTestText.c_str());

	Loop();

	endwin();
}

void Screen::Initialize()
{
	running = true;
	screenThread = new std::thread(&Screen::Display, this);
}

void Screen::Loop()
{
	do
	{

		refresh();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}while(running == true);
}

void Screen::Close()
{
	running = false;
	screenThread->join();
}

