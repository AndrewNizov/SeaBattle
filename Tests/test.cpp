#include "pch.h"
#include "Position.h"
#include "Ship.h"

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