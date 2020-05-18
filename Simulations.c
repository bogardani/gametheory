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
#include "Simulations.h"

void DoMixedSimulations() {
    struct PlayersRoom* room = NULL;
    struct Simulation* simulation = NULL;
    struct NeighbourDistribution* distribution = NULL;
    int simCount = 3;

    //Mixed T as parameter for 8100 participants
    room = CreatePlayersRoom(1.1, 8100, Mixed);
    simulation = CreateSimulation(room, 500000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "mixedT11.txt");

    room->WinPrize = 1.5;
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "mixedT15.txt");

    room->WinPrize = 1.9;
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "mixedT19.txt");

    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //Mixed 1000 participants
    room = CreatePlayersRoom(1.5, 1000, Mixed);
    simulation = CreateSimulation(room, 500000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "mixed1000.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //Matrix 5000 participants
    room = CreatePlayersRoom(1.5, 5000, Mixed);
    simulation = CreateSimulation(room, 500000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "mixed5000.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //Matrix 8100 participants
    room = CreatePlayersRoom(1.5, 8100, Mixed);
    simulation = CreateSimulation(room, 10000000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "mixed8100.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);
}

void DoMatrixSimulations() {
    struct PlayersRoom* room = NULL;
    struct Simulation* simulation = NULL;
    struct NeighbourDistribution* distribution = NULL;
    int simCount = 3;

    //Matrix T as parameter for 8100 participants
    room = CreatePlayersRoom(1.1, 8100, Matrix);
    simulation = CreateSimulation(room, 500000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "matrixT11.txt");

    room->WinPrize = 1.5;
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "matrixT15.txt");

    room->WinPrize = 1.9;
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "matrixT19.txt");

    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //Matrix 1000 participants
    room = CreatePlayersRoom(1.5, 1024, Matrix);
    simulation = CreateSimulation(room, 500000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "matrix1000.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //Matrix 5000 participants
    room = CreatePlayersRoom(1.5, 5041, Matrix);
    simulation = CreateSimulation(room, 500000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "matrix5000.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //Matrix 8100 participants
    room = CreatePlayersRoom(1.5, 8100, Matrix);
    simulation = CreateSimulation(room, 10000000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "matrix8100.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);
}

void DoStrongHeterogenousSimulations() {
    struct PlayersRoom* room = NULL;
    struct Simulation* simulation = NULL;
    struct NeighbourDistribution* distribution = NULL;
    int simCount = 3;

    //StrongHeterogenous T as parameter for 8100 participants
    room = CreatePlayersRoom(1.1, 8100, StrongHeterogenous);
    distribution = CreateNeighbourDistribution(room);
    PrintNeighbourDistributionToFile(distribution, "distribution8100.txt");
    DestroyNeighbourDistribution(distribution);
    simulation = CreateSimulation(room, 10000000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "strongHeterogenousT11.txt");

    room->WinPrize = 1.5;
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "strongHeterogenousT15.txt");

    room->WinPrize = 1.9;
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "strongHeterogenousT19.txt");
    
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);

    //StrongHeterogenous 1000 participants
    room = CreatePlayersRoom(1.5, 1000, StrongHeterogenous);
    distribution = CreateNeighbourDistribution(room);
    PrintNeighbourDistributionToFile(distribution, "distribution1000.txt");
    DestroyNeighbourDistribution(distribution);
    simulation = CreateSimulation(room, 10000000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "strongHeterogenous1000.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);


    //StrongHeterogenous 5000 participants
    room = CreatePlayersRoom(1.5, 5000, StrongHeterogenous);
    distribution = CreateNeighbourDistribution(room);
    PrintNeighbourDistributionToFile(distribution, "distribution5000.txt");
    DestroyNeighbourDistribution(distribution);
    simulation = CreateSimulation(room, 10000000);
    RunSimulation(simulation, simCount);
    PrintResultsToFile(simulation, "strongHeterogenous5000.txt");
    DestroySimulation(simulation);
    DestroyPlayersRoom(room);
}