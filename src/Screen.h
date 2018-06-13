//
// Created by waxta on 23.05.18.
//

#pragma once

#include <thread>
#include <vector>
#include "Drawable.h"
#include "Granary.h"
#include "Plantation.h"
#include "Queen.h"
#include "King.h"

class Screen
{
public:
	Screen();
	~Screen();

	void StartRunning();
	void Close();
	void SetWorkersVector(std::vector<Worker> *workers);
	void SetGranary(Granary * granary);
	void SetPlantation(Plantation * plantation);
	void SetQueen(Queen * queen);
	void SetKing(King * king);

private:
	std::thread * screenThread;
	unsigned int ScreenXSize, ScreenYSize;
	bool working;
	std::vector<unsigned int> deadWorkers;
	void DeleteDeadWorkers();

	void Loop();
	void DrawWorkers();
	void DrawGranary();
	void DrawPlantation();
	void DrawQueen();
	void DrawKing();
	std::vector<Drawable *> drawables;
	std::vector<Worker> * workers;
	Granary * granary;
	Plantation * plantation;
	Queen * queen;
	King * king;
};


