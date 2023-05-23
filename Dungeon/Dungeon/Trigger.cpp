#include "Trigger.h"
#include "Game.h"

Trigger::Trigger(const Trigger& ref) { *this = ref; }

void Trigger::update(Hero& hero) const {
	if (hero.getPos().x == tPos.x && hero.getPos().y == tPos.y) {
		hero.gainEXP(tExp);
	}
}

// Set position
void Trigger::setPos(const Position& pos) { this->tPos = pos; }
void Trigger::setPos(int x, int y) {
	this->tPos.x = x;
	this->tPos.y = y;
}

// Get position
Position Trigger::getPos() const { return this->tPos; }

// Get Icon
char Trigger::getIcon() const { return this->tIcon; }

int Trigger::getExpAmount() const { return this->tExp; }