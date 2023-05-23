#include "Creature.h"
#include "Game.h"

// Default constructor
Creature::Creature(void) {
	this->sPos.x = 1;
	this->sPos.y = 1;
	this->sIcon = 'C';
	this->power = 5;
};

// Set position
void Creature::setPos(Position pos) { this->sPos = pos; }
void Creature::setPos(int x, int y) {
	this->sPos.x = x;
	this->sPos.y = y;
}

// Set icon
void Creature::setIcon(char& icon) { this->sIcon = icon; }

// Get position
Position Creature::getPos(void) { return this->sPos; }

// Get Icon
char Creature::getIcon(void) { return this->sIcon; }

void Creature::update(Hero& hero, char** board) {
	Position hPos = hero.getPos();

	Position dir;
	if (canSee(this->sPos, hPos, dir)) {
		std::cout << "Creature has found the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
		this->sIcon = '!';
	}
	else {
		std::cout << "Creature didn't find the Hero\n";
		this->sIcon = 'C';
	}

	if (!(hPos != sPos)) {
		hero.damage(power);
	}
}

float Creature::clip(float n, float minimun, float maximum) {
	return std::max(minimun, std::min(n, maximum));
}

bool Creature::canSee(Position cPos, Position hPos, Position& dir) {
	// the dir_x and dir_y value are call-by-refernce
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f); // clip the value between -1 ~ 1
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	int count = 0;
	do {
		// spot the target position
		if (cPos + dir * count == hPos) {
			return true;
		}
		count++;
	} while (count < 4); // check the range in 4 units
	return false;
}

bool Creature::canMove(int deltaX, int deltaY, char** board) {
	// Implement Creature controls
	//create a buffer to store the result of trying
	Position tryMove;
	tryMove.x = this->sPos.x + deltaX;
	tryMove.y = this->sPos.y + deltaY;

	//if the try result is valid, move the character
	//else do nothing
	return tryMove.isPositionValid(board);
}

// Incrementally move the elements 
void Creature::move(int deltaX, int deltaY) {
	this->sPos.x += deltaX;
	this->sPos.y += deltaY;
}