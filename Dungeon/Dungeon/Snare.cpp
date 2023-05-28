#include "Snare.h"

Snare::Snare() : Item() {
	tExp = -10;
	tIcon = 'S';
}

Snare::Snare(int x, int y) : Item(x, y) {
	tExp = -10;
	tIcon = 'S';
}

Snare::Snare(const Snare& ref) { *this = ref; }

void Snare::update(Hero& hero) const {
	if (hero.getPos().x == tPos.x && hero.getPos().y == tPos.y) {
		hero.loseEXP(tExp);
	}
}

// Set position
void Snare::setPos(const Position& pos) { this->tPos = pos; }
void Snare::setPos(int x, int y) {
	this->tPos.x = x;
	this->tPos.y = y;
}

// Get position
Position Snare::getPos() const { return this->tPos; }

// Get Icon
char Snare::getIcon() const { return this->tIcon; }

int Snare::getExpAmount() const { return this->tExp; }