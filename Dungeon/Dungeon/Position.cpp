#include "Position.h"

Position::Position() {
	this->x = 1;
	this->y = 1;
}

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

Position::Position(const Position& ref) {
	(*this) = ref;
}