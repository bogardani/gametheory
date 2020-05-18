#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "Player.h"
#include "PlayersRoom.h"

void _createConnection(struct Player* player1, struct Player* player2) {
	AddNeighbour(player1, player2);
	AddNeighbour(player2, player1);
}

void _generateMixedTopology(struct PlayersRoom* this) {
	for (int i = 0; i < this->PlayersLength; i++) {
		for (int k = i + 1; k < this->PlayersLength; k++) {
			int r = rand();
			if (r % 100 == 0) {
				_createConnection(this->Players[i], this->Players[k]);
			}
		}
	}
}

void _generateMatrixTopology(struct PlayersRoom* this) {
	int edge = (int)sqrt(this->PlayersLength);
	if (edge * edge != this->PlayersLength) {
		printf("Invalid Matrix");
		exit(1);
	}
	for (int i = 0; i < this->PlayersLength; i++) {
		int rightNeigbour = i + 1;
		if (i % edge == edge - 1) {
			rightNeigbour = i - edge + 1;
		}
		_createConnection(this->Players[i], this->Players[rightNeigbour]);
		int downNeighbour = i + edge;
		if (i + edge > this->PlayersLength - 1) {
			downNeighbour = i + edge - this->PlayersLength;
		}
		_createConnection(this->Players[i], this->Players[downNeighbour]);
	}
}

void _generateFixedMixedTopology(struct PlayersRoom* this) {

}

void _generateStrongHeterogenousTopology(struct PlayersRoom* this) {
	struct Player** addedPlayers = NULL;
	int addedPlayersCount = 0;
	_createConnection(this->Players[0], this->Players[1]);
	_createConnection(this->Players[0], this->Players[2]);
	_createConnection(this->Players[1], this->Players[2]);
	for (int i = 3; i < this->PlayersLength; i++) {
		int sumNeighbours = 0;
		for (int k = 0; k < i; k++) {
			sumNeighbours += this->Players[k]->NeighboursLength;
		}
		int r = rand();
		int nextConnectionChance = r % sumNeighbours;
		int connectedNeighbourIndex1 = 0;
		int currentLength = 0;
		while (this->Players[connectedNeighbourIndex1]->NeighboursLength < nextConnectionChance - currentLength) {
			currentLength += this->Players[connectedNeighbourIndex1]->NeighboursLength;
			connectedNeighbourIndex1++;
		}
		struct Player* connectedPlayer1 = this->Players[connectedNeighbourIndex1];

		sumNeighbours -= connectedPlayer1->NeighboursLength;
		r = rand();
		nextConnectionChance = r % sumNeighbours;
		int connectedNeighbourIndex2 = 0;
		currentLength = 0;
		if (connectedNeighbourIndex1 == 0 && nextConnectionChance < connectedPlayer1->NeighboursLength) {
			connectedNeighbourIndex2 = 1;
		}
		while (this->Players[connectedNeighbourIndex2]->NeighboursLength < nextConnectionChance - currentLength) {
			if (connectedNeighbourIndex2 == connectedNeighbourIndex1) {
				connectedNeighbourIndex2++;
			}
			else {
				currentLength += this->Players[connectedNeighbourIndex2]->NeighboursLength;
				connectedNeighbourIndex2++;
			}
		}
		struct Player* connectedPlayer2 = this->Players[connectedNeighbourIndex2];
		_createConnection(this->Players[i], connectedPlayer1);
		_createConnection(this->Players[i], connectedPlayer2);
	}
}

void _createPlayers(struct PlayersRoom* this) {
	for (int i = 0; i < this->PlayersLength; i++) {
		int r = rand();
		this->Players[i] = CreatePlayer(r % 2, 10);
	}
}

double _getMatchResult(struct PlayersRoom* this, struct Player* player, struct Player* opponent) {
	int retVal = 0;
	if (player->Strategy == Coop && opponent->Strategy == Coop) {
		return 1;
	}
	else if (player->Strategy == Coop && opponent->Strategy == Cheat) {
		return 0;
	}
	else if (player->Strategy == Cheat && opponent->Strategy == Coop) {
		return this->WinPrize;
	}
	else {
		return 0;
	}
}

double _getPlayerPrize(struct PlayersRoom *this, struct Player* player) {
	double retVal = 0;
	for (int i = 0; i < player->NeighboursLength; i++) {
		retVal += _getMatchResult(this, player, player->Neighbours[i]);
	}
	return retVal;
}

void _learnStrategy(struct PlayersRoom* this, struct Player* player, struct Player* opponent) {
	if (player->Strategy != opponent->Strategy) {
		double playerWins = _getPlayerPrize(this, player);
		double opponentWins = _getPlayerPrize(this, opponent);
		if (opponentWins > playerWins) {
			double dP = opponentWins - playerWins;
			double pMax = (player->NeighboursLength > opponent->NeighboursLength ? player->NeighboursLength : opponent->NeighboursLength)* this->WinPrize;
			double learnChance = exp(-dP / pMax);
			int r = rand();
			if (r % 1000 < (int)(learnChance * 1000)) {
				player->Strategy = opponent->Strategy;
			}
		}
	}
}

struct PlayersRoom* CreatePlayersRoom(double winPrize, int playersLength, enum Topology topology) {
	struct PlayersRoom* playersRoom = NULL;
	playersRoom = (struct PlayersRoom*)malloc(sizeof(struct PlayersRoom));
	if (playersRoom) {
		playersRoom->WinPrize = winPrize;
		playersRoom->PlayersLength = playersLength;
		playersRoom->Players = NULL;
		playersRoom->Players = (struct Player**)malloc(playersRoom->PlayersLength * sizeof(struct Player*));
		if (playersRoom->Players) {
			_createPlayers(playersRoom);

			switch (topology)
			{
			case Mixed:
				_generateMixedTopology(playersRoom);
				break;
			case Matrix:
				_generateMatrixTopology(playersRoom);
				break;
			case FixedMixed:
				_generateFixedMixedTopology(playersRoom);
				break;
			case StrongHeterogenous:
				_generateStrongHeterogenousTopology(playersRoom);
				break;
			default:
				break;
			}
		}
	}

	return playersRoom;
}

void Play(struct PlayersRoom* this) {
	int r = rand();
	struct Player* player = this->Players[r % this->PlayersLength];
	r = rand();
	struct Player* opponent = player->Neighbours[r % player->NeighboursLength];
	_learnStrategy(this, player, opponent);
}

double GetCoopRatio(struct PlayersRoom* this) {
	int coopCount = 0;
	for (int i = 0; i < this->PlayersLength; i++) {
		if (this->Players[i]->Strategy == Coop) {
			coopCount++;
		}
	}

	return (double)coopCount / (double)this->PlayersLength;
}

int GetMaxNeighbourCount(struct PlayersRoom* this) {
	int retVal = 0;

	for (int i = 0; i < this->PlayersLength; i++) {
		if (this->Players[i]->NeighboursLength > retVal) {
			retVal = this->Players[i]->NeighboursLength;
		}
	}

	return retVal;
}

void ResetRoom(struct PlayersRoom* this) {
	for (int i = 0; i < this->PlayersLength; i++) {
		Reset(this->Players[i]);
	}
}

void DestroyPlayersRoom(struct PlayersRoom *this) {
	for (int i = 0; i < this->PlayersLength; i++) {
		DestroyPlayer(this->Players[i]);
	}
	free(this->Players);
	free(this);
}