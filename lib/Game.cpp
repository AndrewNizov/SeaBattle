#include "Game.h"

Game::Game(const std::string& p1Name, const std::string& p2Name)
    : player1(p1Name), player2(p2Name), state(GameState::NotStarted) {}

Player& Game::getPlayer1() { return player1; }
Player& Game::getPlayer2() { return player2; }
GameState Game::getState() const { return state; }

void Game::start() 
{
    state = GameState::Player1Turn;
}

bool Game::makeMove(Position target)
{
    if (state != GameState::Player1Turn && state != GameState::Player2Turn)
    {
        return false;
    }

    Player& defender = (state == GameState::Player1Turn) ? player2 : player1;
    CellState result = defender.getField().shoot(target);

    if (defender.isDefeated())
    {
        state = GameState::Finished;
        return true;
    }

    if (result == CellState::Miss)
    {
        state = (state == GameState::Player1Turn) ? GameState::Player2Turn : GameState::Player1Turn;
    }

    return true;
}

Player* Game::getWinner() const
{
    if (state != GameState::Finished) return nullptr;
    if (player2.isDefeated()) return const_cast<Player*>(&player1);
    if (player1.isDefeated()) return const_cast<Player*>(&player2);
    return nullptr;
}