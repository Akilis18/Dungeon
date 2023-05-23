#include "Position.h"

Position::Position(const Position& ref) { *this = ref; }

//bool Position::isPositionValid(Position& pos, char** gBoard) {
//	// Check whether it is an empty space
//	if (gBoard[pos.y][pos.x] != ' ')
//		return false;
//
//	return true;
//}

bool Position::isPositionValid(char** board) {
	// Check whether it is an empty space
	if (board[this->y][this->x] != ' ') {
		return false;
	}

	return true;
}

// Operator overloading
Position Position::operator+(const Position& rhs) const {
	return Position(x + rhs.x, y + rhs.y);
}

Position& Position::operator+=(const Position& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Position Position::operator-(const Position& rhs) const {
	return Position(x - rhs.x, y - rhs.y);
}

Position& Position::operator-=(const Position& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Position Position::operator*(int scale) const {
	return Position(x * scale, y * scale);
}

bool Position::operator==(const Position& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Position::operator!=(const Position& rhs) const {
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& oStream, const Position& pos) {
	return oStream << pos.x << " " << pos.y;
}

std::istream& operator>>(std::istream& iStream, Position& pos) {
	return iStream >> pos.x >> pos.y;
}