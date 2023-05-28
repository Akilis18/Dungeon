#pragma once
#include "Creature.h"

class Bug : public Creature {
public:
	//Intent: Default constructor
	//Pre: None
	//Post: Members assigned
	Bug();

	// function overriding
	void update(Hero& hero, char** board) override;
	virtual bool canSee(Position cPos, Position hPos, Position& dir) override;
	virtual bool canMove(int deltaX, int deltaY, char** board) override;
	virtual void move(int deltaX, int deltaY) override;
};