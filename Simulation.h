#ifndef SIMULATION_H
#define SIMULATION_H

struct Simulation {
	struct PlayersRoom* _playersRoom;
	int _simCount;
	double* results;
};

struct Simulation* CreateSimulation(struct PlayersRoom* playersRoom, int simCount);

void RunSimulation(struct Simulation* this, int runCount);

void PrintResults(struct Simulation* this);

void PrintResultsToFile(struct Simulation* this, char* fileName);

void DestroySimulation(struct Simulation* this);

#endif
