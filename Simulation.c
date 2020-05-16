#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "PlayersRoom.h"
#include "Simulation.h"
#include "NeighbourDistribution.h"

struct Simulation* CreateSimulation(struct PlayersRoom* playersRoom, int simCount) {
	struct Simulation* simulation = NULL;
	simulation = (struct Simulation*)malloc(sizeof(struct Simulation));
	if (simulation) {
		simulation->_playersRoom = playersRoom;
		simulation->_simCount = simCount;
		simulation->results = (double*)malloc(simCount * sizeof(double));
	}

	return simulation;
}

void RunSimulation(struct Simulation* this) {
	for (int i = 0; i < this->_simCount; i++) {
		Play(this->_playersRoom);
		this->results[i] = GetCoopRatio(this->_playersRoom);
	}
}

void PrintResults(struct Simulation* this) {
	for (int i = 0; i < this->_simCount; i++) {
		printf("%f\n", this->results[i]);
	}
}

void PrintResultsToFile(struct Simulation* this, char* fileName) {
	FILE* fp;
	fp = fopen(fileName, "w+");
	for (int i = 0; i < this->_simCount; i++)
	{
		fprintf(fp, "%d\t%.3f\n", i, this->results[i]);
	}
	fclose(fp);
}

void DestroySimulation(struct Simulation* this) {
	free(this->results);
	free(this);
}