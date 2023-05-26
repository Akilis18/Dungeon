#pragma once
#include <iostream>

//************************************************************
// The location in the board
//************************************************************
class Position {
public:
	int x, y; // x, y Coordinate

	Position() : x(0), y(0) {}
	Position(int x, int y) : x(x), y(y) {}
	Position(const Position& ref);

	//check if position valid
	bool isPositionValid(char** board);

	// Operator overloading
	Position operator+(const Position& rhs) const;
	Position& operator+=(const Position& rhs);
	Position operator-(const Position& rhs) const;
	Position& operator-=(const Position& rhs);
	Position operator*(int scale) const;

	bool operator==(const Position& rhs) const;
	bool operator!=(const Position& rhs) const;

	friend std::ostream& operator<<(std::ostream& oStream, const Position& pos);
	friend std::istream& operator>>(std::istream& iStream, Position& pos);
};
