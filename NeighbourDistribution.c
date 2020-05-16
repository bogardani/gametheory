#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "Player.h"
#include "PlayersRoom.h"
#include "NeighbourDistribution.h"

void _createDistributions(struct NeighbourDistribution* this) {
	for (int i = 0; i < this->DistributionsLength; i++) {
		this->Distributions[i] = 0;
	}
}

struct NeighbourDistribution* CreateNeighbourDistribution(struct PlayersRoom* playersRoom) {
	struct NeighbourDistribution* neighbourDistribution = NULL;
	neighbourDistribution = (struct NeighbourDistribution*)malloc(sizeof(struct NeighbourDistribution));
	if (neighbourDistribution) {
		neighbourDistribution->Distributions = NULL;
		neighbourDistribution->DistributionsLength = GetMaxNeighbourCount(playersRoom) + 1;
		neighbourDistribution->Distributions = (int*)malloc(neighbourDistribution->DistributionsLength * sizeof(int));
		if (neighbourDistribution->Distributions) {
			_createDistributions(neighbourDistribution);

			for (int i = 0; i < playersRoom->PlayersLength; i++) {
				neighbourDistribution->Distributions[playersRoom->Players[i]->NeighboursLength]++;
			}
		}
	}
	
	return neighbourDistribution;
}

void PrintNeighbourDistribution(struct NeighbourDistribution* this) {
	for (int i = 0; i < this->DistributionsLength; i++) {
		printf("%d\t%d\n", i, this->Distributions[i]);
	}
}

void PrintNeighbourDistributionToFile(struct NeighbourDistribution* this, char* fileName) {
	FILE* fp;
	fp = fopen(fileName, "w+");
	for (int i = 0; i < this->DistributionsLength; i++)
	{
		fprintf(fp, "%d\t%d\n", i, this->Distributions[i]);
	}
	fclose(fp);
}

void DestroyNeighbourDistribution(struct NeighbourDistribution* this) {
	free(this->Distributions);
	free(this);
}