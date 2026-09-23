#include "Ship.h"

Ship::Ship(Position start, int size, Orientation orientation)
	:startPosition(start), size(size), orientation(orientation), hits(0) {}

Position Ship::getStartPosition() const
{
	return startPosition;
}

int Ship::getSize()const
{
	return size;
}

Orientation Ship::getOrientation()const
{
	return orientation;
}

int Ship::getHits() const
{
	return hits;
}

bool Ship::isSunk() const
{
	return hits >= size;
}

void Ship::takeHits()
{
	if (hits < size)hits++;
}
std::vector<Position> Ship::getOccupiedPositions() const
{
	std::vector<Position> positions;
	for (int i = 0; i < size; ++i)
	{
		if (orientation == Orientation::Horizontal)
			positions.push_back(Position(startPosition.x + i, startPosition.y));
		else
			positions.push_back(Position(startPosition.x, startPosition.y + i));
	}
	return positions;
}