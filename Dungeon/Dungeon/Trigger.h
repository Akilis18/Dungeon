#pragma once
#include <string>
#include <iostream>

#include "Item.h"
#include "Position.h"
#include "Hero.h"

//************************************************************
// A Trigger class
//************************************************************
class Trigger : public Item {
public:
	//Intent: Default constructor
	//Pre: None
	//Post: Members assigned
	Trigger();

	//Intent: Constructor
	//Pre: int x, int y
	//Post: Members assigned
	Trigger(int x, int y);

	//Intent: Default constructor
	//Pre: Object reference
	//Post: Members assigned
	Trigger(const Trigger& ref);

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