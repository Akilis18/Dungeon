#include "Snare.h"

//Intent: Default constructor
//Pre: None
//Post: Members assigned
Snare::Snare() : Item() {
	tExp = -10;
	tIcon = 'S';
}

//Intent: Constructor
//Pre: int x, int y
//Post: Members assigned
Snare::Snare(int x, int y) : Item(x, y) {
	tExp = -10;
	tIcon = 'S';
}

//Intent: Default constructor
//Pre: Object reference
//Post: Members assigned
Snare::Snare(const Snare& ref) { *this = ref; }

//Intent: Update Hero's info
//Pre: Hero object
//Post: Hero's info 
void Snare::update(Hero& hero) const {
	if (hero.getPos().x == tPos.x && hero.getPos().y == tPos.y) {
		hero.loseEXP(tExp);
	}
}


//Intent: Set Position
//Pre: Position or its coordinates
//Post: Position assigned
void Snare::setPos(const Position& pos) { this->tPos = pos; }
void Snare::setPos(int x, int y) {
	this->tPos.x = x;
	this->tPos.y = y;
}

//Intent: Get position
//Pre: None
//Post: A const Position
Position Snare::getPos() const { return this->tPos; }

//Intent: Get Icon
//Pre: None
//Post: icon as const char
char Snare::getIcon() const { return this->tIcon; }

//Intent: Get reward value
//Pre: None
//Post: tExp as const int
int Snare::getExpAmount() const { return this->tExp; }
