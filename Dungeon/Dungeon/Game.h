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
#include "Trigger.h"
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

	void keyUpdate(bool key[]);

	void update(bool key[]);

	void setupBoard(int rowN, int colN);

	void draw();

	void drawInfo();

	void saveMap();
	void loadMap();

public:
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

	//vector<Creature*> gCreature;
	Creature gCreature;

	vector<Trigger*> gTriggers;

	/*for (auto it = gCreature.begin(); it != gCreature.end(); it++)
		if (*it != nullptr)
			it->.....()

	gTriggers.push_back(new TriggerA(...));
	for (auto it = gTriggers.begin(); it != gTriggers.end(); it++)
		if (*it != nullptr)
			it->.....()*/

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

	bool gKeyState[ValidInput::INVALID];
};