#ifndef NEIGHBOUR_DISTRIBUTION_H
#define NEIGHBOUR_DISTRIBUTION_H

struct NeighbourDistribution {
	int* Distributions;
	int DistributionsLength;
};

struct NeighbourDistribution* CreateNeighbourDistribution(struct PlayersRoom* playersRoom);

void PrintNeighbourDistribution(struct NeighbourDistribution* this);

void PrintNeighbourDistributionToFile(struct NeighbourDistribution* this, char* fileName);

void DestroyNeighbourDistribution(struct NeighbourDistribution* this);

#endif
