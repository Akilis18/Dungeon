#pragma once
//include libraries
#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <ctime>		// for time loop function
#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>	// for max and min function
#include <vector>
#include <fstream>

//include our header files
//#include "Board.h"
#include "Hero.h"
#include "Creature.h"
#include "Bug.h"
#include "Item.h"
#include "Snare.h"
#include "Trigger.h"
#include "Replenish.h"
#include "Position.h"

using namespace std;

class Game {
public:
	//Intent: Default constructor
	//Pre: None
	//Post: None
	Game() {};

	//Intent: Default destructor
	//Pre: None
	//Post: None
	~Game() {};

	//Intent: Main game flow
	//Pre: None
	//Post: No return
	void mainFlow();

	//Intent: Update key state
	//Pre: key managing array
	//Post: update key array
	void keyUpdate(bool key[]);

	//Intent: Update all characters' states
	//Pre: key array
	//Post: Update all characters' states
	void update(bool key[]);

	//Intent: setup the game board
	//Pre: int rowN, int colN
	//Post: game board created
	void setupBoard(int rowN, int colN);

	//Intent: draw the game board
	//Pre: None
	//Post: game board printed on the screen
	void draw();

	//Intent: Draw each character's info
	//Pre: None
	//Post: Info printed on console
	void drawInfo();

	//Intent: Save current game data
	//Pre: None
	//Post: Game data saved in a text file
	void saveMap();

	//Intent: Load game data from file
	//Pre: None
	//Post: Game reset
	void loadMap();

private:
	const double gTimeLog = 0.033;

	//store characters
	//Board gBoard;
	char** gBoard;
	const char WALL = 'O';
	const char NOTHING = ' ';

	int GWIDTH, GHEIGHT;
	const int MIN_SIZE = 4;
	//const int gDistance = 4;

	Hero gHero;

	//Creature gCreature;
	vector<Creature*> gCreatures = { new Creature(), new Bug() };

	//vector<Trigger*> gTriggers;
	vector<Item*> gItems = { new Trigger(), new Snare(), new Replenish() };

	//Enumerate different key state
	enum ValidInput {
		EW = 0,
		ES = 1,
		EA = 2,
		ED = 3,
		ESPACE = 4,
		EESC = 5,
		ESave = 6,
		ELoad = 7,
		INVALID,
	};

	//For key state management
	bool gKeyState[ValidInput::INVALID];
};