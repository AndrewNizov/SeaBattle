#pragma once

#include "GameField.h"
#include <string>

class Player
{
    std::string name;
    GameField field;

public:
    Player(const std::string& name = "Player");

    std::string getName() const;
    GameField& getField();
    const GameField& getField() const;

    bool isDefeated() const;
};