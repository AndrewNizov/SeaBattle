#pragma once
#include "Ship.h"
#include "Position.h"
#include <vector>

enum class CellState
{
	Empty,
	Ship,
	Hit,
	Miss
};

class GameField 
{
	static const int SIZE=10;
	CellState grid[SIZE][SIZE];
	std::vector<Ship> ships;

	bool isValidPosition(int x, int y);
	bool canPlaceShip(const Ship& ship) const;

public:
	GameField();

	bool placeShip(const Ship& ship);
	CellState shoot(Position pos);
	CellState getCell(int x, int y);
	bool allShipsSunk() const;
	int getShipsCount() const;
};