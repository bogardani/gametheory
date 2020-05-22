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

void _createResults(struct Simulation* this, double**results, int runCount) {
	for (int i = 0; i < runCount; i++) {
		results[i] = (double*)malloc(this->_simCount * sizeof(double));
	}
}

void _runSimulation(struct Simulation* this, double** results, int runCount) {
	for (int k = 0; k < runCount; k++) {
		ResetRoom(this->_playersRoom);
		for (int i = 0; i < this->_simCount; i++) {
			Play(this->_playersRoom);
			results[k][i] = GetCoopRatio(this->_playersRoom);
		}
	}
	for (int i = 0; i < this->_simCount; i++) {
		double sum = 0;
		for (int k = 0; k < runCount; k++) {
			sum += results[k][i];
		}
		this->results[i] = sum / runCount;
	}
}

void _deleteResults(double** results, int runCount) {
	for (int i = 0; i < runCount; i++) {
		free(results[i]);
	}
	free(results);
}

void RunSimulation(struct Simulation* this, int runCount) {
	double** results = NULL;
	results = (double**)malloc(runCount * sizeof(double*));
	if (results) {
		_createResults(this, results, runCount);
		_runSimulation(this, results, runCount);
	}
	_deleteResults(results, runCount);
	ResetRoom(this->_playersRoom);
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
