#pragma once
#pragma once
#include <string>
#include <iostream>

#include "Position.h"
#include "Hero.h"

class Trigger {
private:
	Position tPos;
	char tIcon;
	int tExp;

public:
	//Intent: Default constructor
	//Pre: None
	//Post: members assigned
	Trigger() : tExp(10) {
		tIcon = 'T';
	}

	//Intent: Constructor
	//Pre: coordinate value
	//Post: members assigned
	Trigger(int x, int y) : tExp(10) {
		tPos.x = x;
		tPos.y = y;
		tIcon = 'T';
	}

	//Intent: Constructor
	//Pre: Trigger reference
	//Post: members assigned
	Trigger(const Trigger& ref);

	//Intent: Update Hero's info
	//Pre: Hero object
	//Post: Hero's info 
	void update(Hero& hero) const;

	//Intent: Set Position
	//Pre: Position or its coordinates
	//Post: Position assigned
	void setPos(const Position& pos);
	void setPos(int x, int y);

	//Intent: Get position
	//Pre: None
	//Post: A const Position
	Position getPos() const;

	//Intent: Get Icon
	//Pre: None
	//Post: icon as const char
	char getIcon() const;

	//Intent: Get reward value
	//Pre: None
	//Post: tExp as const int
	int getExpAmount() const;
};