#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "Player.h"

void _createNeighbours(struct Player* this) {
	for (int i = 0; i < this->_buffSize; i++)
	{
		this->Neighbours[i] = NULL;
	}
}

struct Player* CreatePlayer(enum Strategy strategy, int initBuffSize) {
	if (initBuffSize == 0)
	{
		printf("Invalid buffer size");
		exit(1);
	}

	struct Player* player = NULL;
	player = (struct Player*)malloc(sizeof(struct Player));
	if (player) {
		player->_buffSize = initBuffSize;
		player->Strategy = strategy;
		player->_defaultStrategy = strategy;
		player->Neighbours = NULL;
		player->Neighbours = (struct Player**)malloc(player->_buffSize * sizeof(struct Player*));
		if (player->Neighbours) {
			_createNeighbours(player);
		}
		player->NeighboursLength = 0;
	}
	return player;
}

void _reallocNeighbours(struct Player* this, int buffSize) {
	if (this->_buffSize > buffSize)
	{
		printf("Small buffSize");
		return;
	}
	struct Player** tmp = NULL;
	tmp = realloc(this->Neighbours, buffSize * sizeof(struct Player*));
	if (tmp != NULL) {
		this->Neighbours = tmp;
		for (int i = this->NeighboursLength; i < buffSize; i++) {
			this->Neighbours[i] = NULL;
		}
		this->_buffSize = buffSize;
	}
}

void AddNeighbour(struct Player* this, struct Player* neighbour) {
	if (this->NeighboursLength == this->_buffSize) {

		_reallocNeighbours(this, this->_buffSize + 1);
	}
	for (int i = 0; i < this->NeighboursLength; i++) {
		if (this->Neighbours[i] == neighbour) {
			return;
		}
	}
	this->Neighbours[this->NeighboursLength] = neighbour;
	this->NeighboursLength++;
}

void ClearNeighbours(struct Player* this) {
	free(this->Neighbours);
	this->Neighbours = NULL;
	this->Neighbours = (struct Player**)malloc(this->_buffSize * sizeof(struct Player*));
	if (this->Neighbours) {
		_createNeighbours(this);
	}
	this->NeighboursLength = 0;
}

void Reset(struct Player* this) {
	this->Strategy = this->_defaultStrategy;
}

void DestroyPlayer(struct Player* this) {
	free(this->Neighbours);
	free(this);
}
