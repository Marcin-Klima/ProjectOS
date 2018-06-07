//
// Created by waxta on 23.05.18.
//

#pragma once

#include <thread>
#include <vector>
#include "Drawable.h"
#include "Worker.h"
#include "Granary.h"

class Screen
{
public:
	Screen();
	~Screen();

	void StartRunning();
	void Close();
	void AddDrawable(Drawable &drawable);
	void SetWorkersVector(std::vector<Worker> *workers);
	void SetGranary(Granary * granary);

private:
	std::thread * screenThread;
	unsigned int ScreenXSize, ScreenYSize;
	bool running;

	void Loop();
	void DrawWorkers();
	void DrawGranary();
	std::vector<Drawable *> drawables;
	std::vector<Worker> * workers;
	Granary * granary;
};


