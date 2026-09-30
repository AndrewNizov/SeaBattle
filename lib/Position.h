#pragma once
class Position
{
	int x;
	int y;
public:
	

	Position(int x = 0, int y = 0);
	int getX() const { return x; }
	int getY()const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	bool operator==(const Position& other) const;

};