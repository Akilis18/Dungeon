#pragma once

#include "Position.h"

class Character {
private:
	Position pos;		//x, y coordinate
	char sIcon;		//character's icon

	int sPower;		//character's power
	int sLevel;		//note current level
	int sCurrentExp;//current experience
	int sMaxExp;	//max exp for this level

public:
	//Intent: Default constructor
	//Pre: None
	//Pre: None
	Character() {};
	
	//Intent: Set position
	//Pre: Position object
	//Post: Position value assigned
	virtual void setPos(Position pos) = 0;

	//Intent: Set position
	//Pre: Coordinate values
	//Post: Position value assigned
	virtual void setPos(int x, int y) = 0;

	//Intent: Set icon
	//Pre: char icon
	//Post: icon assigned
	virtual void setIcon(char& icon) = 0;

	//Intent: Set level
	//Pre: int level
	//Post: level value assigned
	virtual void setLevel(int level) = 0;

	//Intent: Set exp
	//Pre: int exp
	//Post: exp value assigned
	virtual void setExp(int exp) = 0;

	//Intent: Set MaxExp
	//Pre: int maxexp
	//Post: maxExp value assigned
	virtual void setMaxExp(int maxexp) = 0;

	//Intent: set hp
	//Pre: int hp
	//Post: hp value assigned
	virtual void setHP(int hp) = 0;

	//Intent: Get position
	//Pre: None
	//Post: return Position object
	virtual Position getPos() = 0;

	//Intent: Get Icon
	//Pre: None
	//Post: return Icon as character
	virtual char getIcon() = 0;

	//Intent: Get level
	//Pre: None
	//Post: return level as integer
	virtual int getLevel() = 0;

	//Intent: Get Exp
	//Pre: None
	//Post: return exp value
	virtual int getExp() = 0;

	//Intent: Get max exp
	//Pre: None
	//Post: return maxExp
	virtual int getMaxExp() = 0;

	//Intent: Get hp
	//Pre: None
	//Post: return hp as const int
	virtual int getHP() const = 0;

	//Intent: Incrementally move the elements
	//Pre: move amount
	//Post: Update position
	virtual void move(Position delta) = 0;

	//Intent: Calculate Gain of EXP
	//Pre: int points
	//Post: compute exp
	virtual void gainEXP(int points) = 0;

	//Intent: Calculate damage
	//Pre: int points
	//Post: compute damage
	virtual void damage(int points) = 0;
};