#include "pch.h"
#include "Position.h"

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