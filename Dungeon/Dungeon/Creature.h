#pragma once
#include "Hero.h"
#include "Position.h"

#include <vector>

using namespace std;

class Creature {//creature class 
protected:
	Position	sPos;			// Creature position
	char sIcon = 'C';			// Creature icon
	int power;
	//vector<int> validDir;

public:
	// Default constructor
	Creature(void);

	// Set position
	void setPos(Position pos);
	void setPos(int x, int y);

	// Set icon
	void setIcon(char& icon);

	// Get position
	Position getPos(void);

	// Get Icon
	char getIcon(void);

	//set update function as virtual because console output should be revised
	virtual void update(Hero& hero, char** board);

	float clip(float n, float minimun, float maximum);

	/* functions that haven't been called in main gameflow yet */

	// Check if the hero is in the creature's sight
	virtual bool canSee(Position cPos, Position hPos, Position& dir);

	// Check if the creature can move to target coordinate
	virtual bool canMove(int deltaX, int deltaY, char** board);

	// Incrementally move the elements
	virtual void move(int deltaX, int deltaY);
};
