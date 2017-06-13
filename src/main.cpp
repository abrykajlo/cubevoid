/* Copyright (C) Adam Brykajlo, Inc - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <simulation.h>

SimulationManager gSimulationManager;

int main(int argc, char** argv)
{
	gSimulationManager.Run();

	return 0;
}