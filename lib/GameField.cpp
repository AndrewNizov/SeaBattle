#include "GameField.h"

GameField::GameField() {
    for (int y = 0; y < SIZE; ++y) {
        for (int x = 0; x < SIZE; ++x) {
            grid[y][x] = CellState::Empty;
        }
    }
}

bool GameField::isValidPosition(int x, int y) const {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool GameField::canPlaceShip(const Ship& ship) const {
    auto positions = ship.getOccupiedPositions();

    for (const auto& pos : positions) {
        if (!isValidPosition(pos.x, pos.y)) {
            return false;
        }
    }
    for (const auto& pos : positions)
    {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int nx = pos.x + dx;
                int ny = pos.y + dy;

                if (isValidPosition(nx, ny)) {
                    if (grid[ny][nx] == CellState::Ship) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool GameField::placeShip(const Ship& ship) {
    if (!canPlaceShip(ship)) return false;

    ships.push_back(ship);
    auto positions = ship.getOccupiedPositions();
    for (const auto& pos : positions) {
        grid[pos.y][pos.x] = CellState::Ship;
    }
    return true;
}

CellState GameField::shoot(Position pos) {
    if (!isValidPosition(pos.x, pos.y)) return CellState::Empty;

    if (grid[pos.y][pos.x] == CellState::Ship) {
        grid[pos.y][pos.x] = CellState::Hit;

        for (auto& ship : ships) {
            auto positions = ship.getOccupiedPositions();
            for (const auto& shipPos : positions) {
                if (shipPos == pos) {
                    ship.takeHits();
                    break;
                }
            }
        }
        return CellState::Hit;
    }
    else if (grid[pos.y][pos.x] == CellState::Hit || grid[pos.y][pos.x] == CellState::Miss) {
        return grid[pos.y][pos.x];
    }
    else {
        grid[pos.y][pos.x] = CellState::Miss;
        return CellState::Miss;
    }
}

CellState GameField::getCell(int x, int y) const {
    if (!isValidPosition(x, y)) return CellState::Empty;
    return grid[y][x];
}

bool GameField::allShipsSunk() const {
    if (ships.empty()) return false;
    for (const auto& ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return true;
}

int GameField::getShipsCount() const {
    return static_cast<int>(ships.size());
}