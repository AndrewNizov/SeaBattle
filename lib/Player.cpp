#include "Player.h"

Player::Player(const std::string& name) : name(name) {}

std::string Player::getName() const { return name; }
GameField& Player::getField() { return field; }
const GameField& Player::getField() const { return field; }

bool Player::isDefeated() const
{
    return field.allShipsSunk();
}