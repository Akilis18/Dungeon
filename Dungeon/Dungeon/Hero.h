#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

#include "Position.h"

using namespace std;

//************************************************************
// A Hero class
//************************************************************
class Hero {

private:
	Position sPos;	// Hero location
	char sIcon;		// Hero icon
	int	hp;			// Life
	int	sLevel;     // Level
	int	sMaxExp;	// Level update experience
	int	sCurrentExp;// current exp hero has

public:
	// Default constructor
	Hero();
	// Setting constructor
	Hero(int x, int y, int level, int maxExp, int currentExp, char icon, int hp);

	// Setting constructor
	Hero(Position& pos, int level, int maxExp, int currentExp, char icon, int hp);

	// Set position
	void setPos(Position pos);
	void setPos(int x, int y);

	// Set icon
	void setIcon(char& icon);

	// Set level
	void setLevel(int level);

	// Set exp
	void setExp(int exp);

	// Set MaxExp
	void SetMaxExp(int maxexp);

	// Get position
	Position getPos(void);

	// Get Icon
	char getIcon(void);

	// Get level
	int getLevel(void);

	// Get Exp
	int getExp(void);

	// Get Max
	int getMaxExp(void);

	// Get hp
	int getHP() const;

	// Set hp
	void setHP(int hp);

	// Incrementally move the elements 
	void move(Position delta, char** board);

	// Calculate Gain of EXP
	void gainEXP(int points);

	// Calculate Loss of Exp
	void loseEXP(int points);

	// Calculate how much hp should be restored
	void gainHP(int points);

	// Calculate how much damage should be casted
	void damage(int points);
};