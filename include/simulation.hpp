#pragma once

class SimulationManager
{
public:
	SimulationManager();
	~SimulationManager();

	int Run();

private:
	void Quit();

	bool quit_;
};

int BigInit();
int BigQuit();