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

int main()
{
    srand((unsigned)time(NULL));
    struct PlayersRoom* room = NULL;
    struct Simulation* simulation = NULL;
    struct NeighbourDistribution* distribution = NULL;


    room = CreatePlayersRoom(1.5, 8100, Mixed);
    simulation = CreateSimulation(room, 1000000);
    RunSimulation(simulation);
    PrintResultsToFile(simulation, "mixed.txt");

    DestroySimulation(simulation);
    DestroyPlayersRoom(room);


    room = CreatePlayersRoom(1.5, 8100, Matrix);
    simulation = CreateSimulation(room, 1000000);
    distribution = CreateNeighbourDistribution(room);
    RunSimulation(simulation);
    PrintResultsToFile(simulation, "matrix.txt");
    PrintNeighbourDistributionToFile(distribution, "distribution.txt");

    DestroyNeighbourDistribution(distribution);
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);


    room = CreatePlayersRoom(1.5, 8100, StrongHeterogenous);
    simulation = CreateSimulation(room, 1000000);
    RunSimulation(simulation);
    PrintResultsToFile(simulation, "strongHeterogenous.txt");
    
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    return 1;
}
