/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include <simulation/simulation.h>

#include <SDL2/SDL.h>


SimulationManager gSimulationManager;

int main(int argc, char** argv)
{
	//Initialize and catch errors
	if (BigInit() < 0)
	{
		return -1;
	}
	//run main loop
	gSimulationManager.Run();
	//Quit and catch errors
	if (BigQuit() < 0)
	{
		return -1;
	}
	return 0;
}