#include "Trigger.h"

//Intent: Default constructor
//Pre: None
//Post: Members assigned
Trigger::Trigger() : Item() {
	tExp = 10;
	tIcon = 'T';
}

//Intent: Constructor
//Pre: int x, int y
//Post: Members assigned
Trigger::Trigger(int x, int y) : Item(x, y) {
	tExp = 10;
	tIcon = 'T';
}

//Intent: Default constructor
//Pre: Object reference
//Post: Members assigned
Trigger::Trigger(const Trigger& ref) { *this = ref; }
	
//Intent: Update Hero's info
//Pre: Hero object
//Post: Hero's info 
void Trigger::update(Hero& hero) const {
	if (hero.getPos().x == tPos.x && hero.getPos().y == tPos.y) {
		hero.gainEXP(tExp);
	}
}

//Intent: Set Position
//Pre: Position or its coordinates
//Post: Position assigned
void Trigger::setPos(const Position& pos) { this->tPos = pos; }
void Trigger::setPos(int x, int y) {
	this->tPos.x = x;
	this->tPos.y = y;
}

//Intent: Get position
//Pre: None
//Post: A const Position
Position Trigger::getPos() const { return this->tPos; }

//Intent: Get Icon
//Pre: None
//Post: icon as const char
char Trigger::getIcon() const { return this->tIcon; }

//Intent: Get reward value
//Pre: None
//Post: tExp as const int
int Trigger::getExpAmount() const { return this->tExp; }
