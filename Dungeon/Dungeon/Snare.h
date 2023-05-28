#pragma once
#include "Item.h"

//************************************************************
// A trap class
//************************************************************
class Snare : public Item {
public:
	//Intent: Default constructor
	//Pre: None
	//Post: Members assigned
	Snare();

	//Intent: Constructor
	//Pre: int x, int y
	//Post: Members assigned
	Snare(int x, int y);

	//Intent: Default constructor
	//Pre: Object reference
	//Post: Members assigned
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