#include <iostream>
#include "Game.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "      Sea Battle  \n";

    Game game("Игрок 1", "Игрок 2");

    game.getPlayer1().getField().placeShip(Ship(Position(0, 0), 2, Orientation::Horizontal));
    game.getPlayer2().getField().placeShip(Ship(Position(5, 5), 1, Orientation::Vertical));

    game.start();
    std::cout << "Игра начата! Ход первого игрока.\n";

    std::cout << "Игрок 1 стреляет в (5, 5)...\n";
    game.makeMove(Position(5, 5));

    if (game.getState() == GameState::Finished && game.getWinner() != nullptr) {
        std::cout << "\nПобеда! Победитель: " << game.getWinner()->getName() << "!\n";
    }

    return 0;
}