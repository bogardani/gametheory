#pragma once

enum Topology {
	Mixed,
	Matrix,
	FixedMixed,
	StrongHeterogenous
};

struct PlayersRoom {
	struct Player** Players;
	int PlayersLength;
	double WinPrize;
};

struct PlayersRoom* CreatePlayersRoom(double winPrize, int playersLength, enum Topology topology);

void Play(struct PlayersRoom* this);

double GetCoopRatio(struct PlayersRoom* this);

int GetMaxNeighbourCount(struct PlayersRoom* this);

void DestroyPlayersRoom(struct PlayersRoom* this);