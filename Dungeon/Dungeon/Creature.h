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
	vector<int> validDir;

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

	void update(Hero& hero, char** board);

	float clip(float n, float minimun, float maximum);
	bool canSee(Position cPos, Position hPos, Position& dir);

	bool canMove(int deltaX, int deltaY, char** board);
	// Incrementally move the elements 
	void move(int deltaX, int deltaY);
};
