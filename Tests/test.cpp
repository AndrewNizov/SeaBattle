#include "pch.h"
#include "Position.h"
#include "Ship.h"
#include "GameField.h"
#include "Player.h"
#include "Game.h"

TEST(PositionTest, Constructor)
{
	Position p1(2, 5);
	Position p2(2, 5);
	Position p3(0, 0);

	EXPECT_EQ(p1.x, 2);
	EXPECT_EQ(p1.y, 5);
	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 == p3);
}
TEST(ShipTest, Creation)
{
	Position start(1, 1);
	Ship ship(start, 3, Orientation::Horizontal);

	EXPECT_EQ(ship.getSize(),3);
	EXPECT_FALSE(ship.isSunk());

	auto positions = ship.getOccupiedPositions();
	EXPECT_EQ(positions.size(), 3);
	EXPECT_EQ(positions[0], Position(1,1));
	EXPECT_EQ(positions[1], Position(2,1));
	EXPECT_EQ(positions[2], Position(3,1));

}

TEST(ShipTest,Sinking)
{
	Position start(0, 0);
	Ship ship(start, 2, Orientation::Vertical);

	EXPECT_FALSE(ship.isSunk());
	ship.takeHits();
	EXPECT_FALSE(ship.isSunk());
	ship.takeHits();
	EXPECT_TRUE(ship.isSunk());

}

TEST(GameFieldTest, PlaceShipShoot)
{
	GameField field;
	Ship ship(Position(0, 0), 2, Orientation::Horizontal);

	EXPECT_TRUE(field.placeShip(ship));
	EXPECT_EQ(field.getShipsCount(), 1);

	EXPECT_EQ(field.shoot(Position(5, 5)), CellState::Miss);
	EXPECT_EQ(field.shoot(Position(0, 0)), CellState::Hit);
	EXPECT_FALSE(field.allShipsSunk());
	EXPECT_EQ(field.shoot(Position(1, 0)), CellState::Hit);
	EXPECT_TRUE(field.allShipsSunk());
}

TEST(GameFieldTest, MoreShips)
{
	GameField field;
	Ship ship1(Position(2, 2), 2, Orientation::Horizontal);
	Ship ship2(Position(2, 2), 2, Orientation::Vertical);
	Ship ship3(Position(3, 3), 1, Orientation::Horizontal);

	EXPECT_TRUE(field.placeShip(ship1));
	EXPECT_FALSE(field.placeShip(ship2));
	EXPECT_FALSE(field.placeShip(ship3));
}

TEST(PlayerTest, InitializationAndDefeat) {
	Player player("Alice");
	EXPECT_EQ(player.getName(), "Alice");
	EXPECT_FALSE(player.isDefeated());

	Ship ship(Position(0, 0), 1, Orientation::Horizontal);
	player.getField().placeShip(ship);
	EXPECT_FALSE(player.isDefeated());

	player.getField().shoot(Position(0, 0));
	EXPECT_TRUE(player.isDefeated());
}

TEST(GameTest, TurnSwitchAndVictory) {
	Game game("Player 1", "Player 2");

	game.getPlayer2().getField().placeShip(Ship(Position(0, 0), 1, Orientation::Horizontal));

	game.start();
	EXPECT_EQ(game.getState(), GameState::Player1Turn);

	game.makeMove(Position(5, 5));
	EXPECT_EQ(game.getState(), GameState::Player2Turn);

	game.makeMove(Position(5, 5));
	EXPECT_EQ(game.getState(), GameState::Player1Turn);

	game.makeMove(Position(0, 0));
	EXPECT_EQ(game.getState(), GameState::Finished);
	ASSERT_NE(game.getWinner(), nullptr);
	EXPECT_EQ(game.getWinner()->getName(), "Player 1");

}

TEST(GameTest, StartOrNot) {
	Game game("Player 1", "Player 2");

	game.getPlayer2().getField().placeShip(Ship(Position(0, 0), 1, Orientation::Horizontal));

	game.start();
	EXPECT_EQ(game.getState(), GameState::Player1Turn);

	game.makeMove(Position(5, 5));
	EXPECT_EQ(game.getState(), GameState::Player2Turn);

	game.makeMove(Position(5, 5));
	EXPECT_EQ(game.getState(), GameState::Player1Turn);

	game.makeMove(Position(0, 0));
	EXPECT_EQ(game.getState(), GameState::Finished);
	ASSERT_NE(game.getWinner(), nullptr);
	EXPECT_EQ(game.getWinner()->getName(), "Player 1");

}