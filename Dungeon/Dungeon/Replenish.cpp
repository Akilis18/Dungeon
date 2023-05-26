#include "Replenish.h"

Replenish::Replenish(const Replenish& ref) { *this = ref; }

void Replenish::update(Hero& hero) const {
	if (hero.getPos().x == tPos.x && hero.getPos().y == tPos.y) {
		hero.gainHP(tExp);
	}
}

// Set position
void Replenish::setPos(const Position& pos) { this->tPos = pos; }
void Replenish::setPos(int x, int y) {
	this->tPos.x = x;
	this->tPos.y = y;
}

// Get position
Position Replenish::getPos() const { return this->tPos; }

// Get Icon
char Replenish::getIcon() const { return this->tIcon; }

int Replenish::getExpAmount() const { return this->tExp; }