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
	enum Strategy _defaultStrategy;
};

struct Player* CreatePlayer(enum Strategy strategy, int initBuffSize);

void AddNeighbour(struct Player* this, struct Player* neighbour);

void ClearNeighbours(struct Player* this);

void Reset(struct Player* this);

void DestroyPlayer(struct Player* this);