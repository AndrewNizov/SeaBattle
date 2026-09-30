#pragma once
#include "Position.h"
#include <vector>

enum class Orientation
{
	Horizontal,
	Vertical
};

class Ship
{
	Position startPosition;
	int size;
	Orientation orientation;
	int hits;
public:
	Ship(Position start, int size, Orientation orientation);

	Position getStartPosition() const;
	int getSize()const;
	Orientation getOrientation()const;
	int getHits() const;

	bool isSunk() const;
	void takeHits();
	std::vector<Position> getOccupiedPositions() const;


};