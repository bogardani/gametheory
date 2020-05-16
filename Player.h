#pragma once

enum Strategy {
	Coop,
	Cheat
};

struct Player {
	struct Player** Neighbours;
	int NeighboursLength;
	int _buffSize;
	enum Strategy Strategy;
};

struct Player* CreatePlayer(enum Strategy strategy, int initBuffSize);

void AddNeighbour(struct Player* this, struct Player* neighbour);

void ClearNeighbours(struct Player* this);

void DestroyPlayer(struct Player* this);