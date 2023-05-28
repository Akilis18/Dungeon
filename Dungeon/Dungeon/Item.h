#pragma once
#include "Position.h"
#include "Hero.h"

//************************************************************
// An Item class (base class)
//************************************************************
class Item {
protected:
	Position tPos;
	char tIcon;
	int tExp;

public:
	//Intent: Default constructor
	//Pre: None
	//Post: members assigned
	Item() {}

	//Intent: Constructor
	//Pre: coordinate value
	//Post: members assigned
	Item(int x, int y) {
		tPos.x = x;
		tPos.y = y;
	}

	//Intent: Constructor
	//Pre: Trigger reference
	//Post: members assigned
	Item(const Item& ref) { *this = ref; }

	//Intent: Update Hero's info
	//Pre: Hero object
	//Post: Hero's info 
	virtual void update(Hero& hero) const = 0;

	//Intent: Set Position
	//Pre: Position or its coordinates
	//Post: Position assigned
	virtual void setPos(const Position& pos) = 0;
	virtual void setPos(int x, int y) = 0;

	//Intent: Get position
	//Pre: None
	//Post: A const Position
	virtual Position getPos() const = 0;

	//Intent: Get Icon
	//Pre: None
	//Post: icon as const char
	virtual char getIcon() const = 0;

	//Intent: Get reward value
	//Pre: None
	//Post: tExp as const int
	virtual int getExpAmount() const = 0;
};