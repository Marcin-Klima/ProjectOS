#include <iostream>
#include "MainApplication.h"

int main()
{
	MainApplication application;
	application.Start();



	application.WaitForUserInput();
	application.Stop();
	return 0;
}