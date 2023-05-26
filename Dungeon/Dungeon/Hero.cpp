#include "Hero.h"

#include "Game.h"

// Default constructor
Hero::Hero() {
	this->sPos.x = 0;
	this->sPos.y = 0;
	this->sLevel = 1;
	this->sCurrentExp = 0;
	this->sMaxExp = 15;
	this->sIcon = 'H';
	this->hp = 100;
};

// Setting constructor
Hero::Hero(int x, int y, int level, int maxExp, int currentExp, char icon, int hp) {
	this->sPos.x = x;
	this->sPos.y = y;
	this->sLevel = level;
	this->sCurrentExp = currentExp;
	this->sMaxExp = maxExp;
	this->sIcon = icon;
	this->hp = hp;
};

// Setting constructor
Hero::Hero(Position& pos, int level, int maxExp, int currentExp, char icon, int hp) {
	this->sPos = pos;
	this->sLevel = level;
	this->sCurrentExp = currentExp;
	this->sMaxExp = maxExp;
	this->sIcon = icon;
	this->hp = hp;
};

// Set position
void Hero::setPos(Position pos) { this->sPos = pos; }
void Hero::setPos(int x, int y) {
	this->sPos.x = x;
	this->sPos.y = y;
}

// Set icon
void Hero::setIcon(char& icon) { this->sIcon = icon; }

// Set level
void Hero::setLevel(int level) { this->sLevel = level; }

// Set exp
void Hero::setExp(int exp) { this->sCurrentExp = exp; }

// Set MaxExp
void Hero::SetMaxExp(int maxexp) { this->sMaxExp = maxexp; }

// Get position
Position Hero::getPos(void) { return this->sPos; }

// Get Icon
char Hero::getIcon(void) { return this->sIcon; }

// Get level
int Hero::getLevel(void) { return this->sLevel; }

// Get Exp
int Hero::getExp(void) { return this->sCurrentExp; }

// Get Max
int Hero::getMaxExp(void) { return this->sMaxExp; }

int Hero::getHP() const { return this->hp; }
void Hero::setHP(int hp) { this->hp = hp; }

// Incrementally move the elements 
void Hero::move(Position delta, char** board) {
	// Compute the next position
	Position next = this->sPos + delta;

	/*if (next.isPositionValid(next, NULL))
		this->sPos = next;*/

	if (next.isPositionValid(board)) {
		this->sPos = next;
	}
	else {
		std::cout << "Invalid location\n";
	}
}

// Calculate Gain of EXP
void Hero::gainEXP(int points) {
	int number = points;
	while (number > 0) {
		if (sCurrentExp + number >= sMaxExp) {//level up
			number -= (sMaxExp - sCurrentExp);
			sCurrentExp = 0;
			sMaxExp = (int)((float)sMaxExp * 1.2f);
			sLevel++;
		}
		else {
			sCurrentExp += number;
			number = 0;
		}
	}
}

// Calculate Loss of EXP
void Hero::loseEXP(int points) {
	int number = -1 * points;
	if (sLevel == 1 && sCurrentExp - number <= 0) {
		sCurrentExp = 0;
		return;
	}

	while (number > 0) {
		if (sCurrentExp - number <= 0) {//level down
			sLevel--;
			number -= sCurrentExp;
			sMaxExp = ceil((float)sMaxExp / 1.2f);
			sCurrentExp = sMaxExp;
		}
		else {
			sCurrentExp -= number;
			number = 0;
		}
	}
}

void Hero::gainHP(int points) {
	hp = hp + points;
	if (hp > 100) {
		hp = 100;
	}
}

void Hero::damage(int points) {
	hp = hp - points;
	if (hp < 0) {
		hp = 0;
	}
}