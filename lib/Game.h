#pragma once
#include "Player.h"

enum class GameState
{
    NotStarted,
    Player1Turn,
    Player2Turn,
    Finished
};

class Game 
{
    Player player1;
    Player player2;
    GameState state;

public:
    Game(const std::string& p1Name = "Player 1", const std::string& p2Name = "Player 2");

    Player& getPlayer1();
    Player& getPlayer2();
    GameState getState() const;


    void start();
    bool makeMove(Position target);
    const Player* getWinner() const;
};