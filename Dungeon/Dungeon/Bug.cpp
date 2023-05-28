#include "Bug.h"

//Intent: Default constructor
//Pre: None
//Post: Members assigned
Bug::Bug() : Creature() {
	this->sIcon = 'B';
	this->power = 2;
}

//Intent: Update the real-time status of bug
//Pre: The hero and the board
//Post: Update each character's status
void Bug::update(Hero& hero, char** board) {
	Position hPos = hero.getPos();

	Position dir;
	if (canSee(this->sPos, hPos, dir)) {
		std::cout << "Bug has found the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
		this->sIcon = '*';
	}
	else {
		std::cout << "Bug didn't find the Hero\n";
		this->sIcon = 'B';
	}

	if (!(hPos != sPos)) {
		hero.damage(power);
	}
}

//Intent: Check if the hero is in the bug's sight
//Pre: The hero and the board
//Post: if the hero is in the bug's sight, return true
bool Bug::canSee(Position cPos, Position hPos, Position& dir) {
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
	} while (count < 2); // check the range in 4 units
	return false;
}

//Intent: Check if the bug can move to target coordinate
//Pre: The X, Y distance and the board
//Post: if the bug can move to target coordinate, return true
bool Bug::canMove(int deltaX, int deltaY, char** board) {
	// Implement Creature controls
	//create a buffer to store the result of trying
	Position tryMove;
	tryMove.x = this->sPos.x + deltaX;
	tryMove.y = this->sPos.y + deltaY;

	//if the try result is valid, move the character
	//else do nothing
	return tryMove.isPositionValid(board);
}

//Intent: Incrementally move the elements 
//Pre: The X, Y distance
//Post: Move the bug to the target position
void Bug::move(int deltaX, int deltaY) {
	this->sPos.x += deltaX;
	this->sPos.y += deltaY;
}
