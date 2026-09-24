#include "GameField.h"
GameField::GameField()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			grid[i][j] = CellState::Empty;
		}
	}
}

bool GameField::isValidPosition(int x, int y) const
{
	return x >= 0 && x < SIZE && y>0 && y < SIZE;
}

bool GameField::canPlaceShip(const Ship& ship) const
{
	auto positions = ship.getOccupiedPositions();
	for (const auto&pos: positions)
	{
		if (!isValidPosition(pos.x, pos.y)) return false;
		for (int dx = -1; dx <= 1; ++dx)
		{
			for (int dy = -1; dy <= 1; ++dy)
			{
				int nx = pos.x + dx;
				int ny = pos.y + dy;
				if (isValidPosition(nx, ny) && grid[nx][ny] == CellState::Ship)
					return false;
			}
		}
	}
	return true;
}

bool GameField::placeShip(const Ship& ship)
{
	if (!canPlaceShip(ship)) return false;

	ships.push_back(ship);
	for (const auto& pos : ship.getOccupiedPositions())
	{
		grid[pos.x][pos.y] = CellState::Ship;
	}return true;
}

CellState GameField::shoot(Position pos)
{
	if (!isValidPosition(pos.x, pos.y)) return CellState::Miss;

	if (grid[pos.x][pos.y] == CellState::Ship)
	{
		grid[pos.x][pos.y] = CellState::Hit;
		for(auto& ship:ships)
			for (const auto& shipPos : ship.getOccupiedPositions())
			{
				if (shipPos == pos)
				{
					ship.takeHits();
					break;
				}
			}
		return CellState::Hit;

	}
	else if (grid[pos.x][pos.y] == CellState::Empty)
	{
		grid[pos.x][pos.y] = CellState::Miss;
		return CellState::Miss;
	}
	return grid[pos.x][pos.y];
}

CellState GameField::getCell(int x, int y)
{
	if (!isValidPosition(x, y))return CellState::Empty;
	return grid[x][y];
}

bool GameField::allShipsSunk() const
{
	if (ships.empty()) return false;
	for (const auto& ship : ships)
	{
		if (!ship.isSunk()) return false;
	}
	return true;
}

int GameField::getShipsCount() const
{
	return static_cast<int>(ships.size());
}