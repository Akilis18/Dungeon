#pragma once

class Position {
public:
	Position();
	Position(int x, int y);
	Position(const Position& ref);

private:
	int x, y;
};