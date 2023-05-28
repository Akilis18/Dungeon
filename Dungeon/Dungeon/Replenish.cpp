#include "Replenish.h"

//Intent: Default constructor
//Pre: None
//Post: Members assigned
Replenish::Replenish() : Item() {
	tExp = 8;
	tIcon = 'R';
}

//Intent: Constructor
//Pre: int x, int y
//Post: Members assigned
Replenish::Replenish(int x, int y) : Item(x, y) {
	tExp = 8;
	tIcon = 'R';
}

//Intent: Default constructor
//Pre: Object reference
//Post: Members assigned
Replenish::Replenish(const Replenish& ref) { *this = ref; }

//Intent: Update Hero's info
//Pre: Hero object
//Post: Hero's info 
void Replenish::update(Hero& hero) const {
	if (hero.getPos().x == tPos.x && hero.getPos().y == tPos.y) {
		hero.gainHP(tExp);
	}
}

//Intent: Set Position
//Pre: Position or its coordinates
//Post: Position assigned
void Replenish::setPos(const Position& pos) { this->tPos = pos; }
void Replenish::setPos(int x, int y) {
	this->tPos.x = x;
	this->tPos.y = y;
}

//Intent: Get position
//Pre: None
//Post: A const Position
Position Replenish::getPos() const { return this->tPos; }

//Intent: Get Icon
//Pre: None
//Post: icon as const char
char Replenish::getIcon() const { return this->tIcon; }

//Intent: Get reward value
//Pre: None
//Post: tExp as const int
int Replenish::getExpAmount() const { return this->tExp; }
