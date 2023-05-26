#pragma once
#include "Item.h"

//A trap object
class Snare : public Item {
public:
	Snare() : Item() {
		tExp = -10;
		tIcon = 'S';
	}

	Snare(const Snare& ref);

	//Intent: Update Hero's info
	//Pre: Hero object
	//Post: Hero's info 
	void update(Hero& hero) const override;

	//Intent: Set Position
	//Pre: Position or its coordinates
	//Post: Position assigned
	void setPos(const Position& pos) override;
	void setPos(int x, int y) override;

	//Intent: Get position
	//Pre: None
	//Post: A const Position
	Position getPos() const override;

	//Intent: Get Icon
	//Pre: None
	//Post: icon as const char
	char getIcon() const override;

	//Intent: Get reward value
	//Pre: None
	//Post: tExp as const int
	int getExpAmount() const override;
};