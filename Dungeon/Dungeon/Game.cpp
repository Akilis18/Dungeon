#include "Game.h"

//Intent: Main game flow
//Pre: None
//Post: No return
void Game::mainFlow() {
	srand(time(NULL));

	// keyboard state management
	bool gKeyState[ValidInput::INVALID];
	for (int i = 0; i < ValidInput::INVALID; i++) {
		gKeyState[i] = false;
	}

	system("cls");
	cout << "Choose difficulty:" << endl
		<< "	[1] Easy" << endl
		<< "	[2] Medium" << endl
		<< "	[3] Hard" << endl
		<< "	[4] Load File" << endl;

	char mode;
	while (mode = _getch()) {
		if (mode == '1') {
			GWIDTH = 9;
			GHEIGHT = 9;
			for (int i = 0; i < 3; i++) {
				gCreatures.push_back(new Bug());
			}
			gItems.push_back(new Replenish());
			gItems.push_back(new Trigger());
			break;
		}
		else if (mode == '2') {
			GWIDTH = 13;
			GHEIGHT = 13;
			for (int i = 0; i < 3; i++) {
				gCreatures.push_back(new Bug());
			}
			for (int i = 0; i < 2; i++) {
				gCreatures.push_back(new Creature());
			}
			gItems.push_back(new Trigger());
			gItems.push_back(new Replenish());
			gItems.push_back(new Snare());
			break;
		}
		else if (mode == '3') {
			GWIDTH = 17;
			GHEIGHT = 17;
			for (int i = 0; i < 4; i++) {
				gCreatures.push_back(new Bug());
			}
			for (int i = 0; i < 3; i++) {
				gCreatures.push_back(new Creature());
			}
			for (int i = 0; i < 2; i++) {
				gItems.push_back(new Trigger());
				gItems.push_back(new Replenish());
				gItems.push_back(new Snare());
			}
			break;
		}
		else if (mode == '4') {
			loadMap();
			break;
		}
		else {
			system("cls");
			cout << mode << " is not available" << endl;

			cout << "Choose difficulty:" << endl
				<< "	[1] Easy" << endl
				<< "	[2] Medium" << endl
				<< "	[3] Hard" << endl
				<< "	[4] Load File" << endl;
		}
	}

	/*while (true) {
		std::cout << "Enter Width: ";
		std::cin >> GWIDTH;
		std::cout << "Enter Height: ";
		std::cin >> GHEIGHT;
		system("CLS");
		if (GHEIGHT < MIN_SIZE || GWIDTH < MIN_SIZE) {
			std::cout << "Illegal, both has to be larger than " << MIN_SIZE << std::endl;
		}
		else {
			break;
		}
	}*/

	system("cls");

	// Setup a clear dungeon
	setupBoard(GHEIGHT, GWIDTH);

	// Draw the board and information
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Run the game loop
	while (!gKeyState[ValidInput::EESC]) {
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog) {
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();

		if (gKeyState[ValidInput::ESave]) {
			try {
				saveMap();
			}
			catch (const exception& e) {
				cerr << "Cannot Save Map" << endl;
			}
			gKeyState[ValidInput::ESave] = false;

			/*saveMap();
			gKeyState[ValidInput::ESave] = false;*/
		}
		else if (gKeyState[ValidInput::ELoad]) {
			try {
				loadMap();
			}
			catch (const exception& e) {
				cerr << "Cannot Load File" << endl;
			}
			gKeyState[ValidInput::ELoad] = false;

			/*loadMap();
			gKeyState[ValidInput::ELoad] = false;*/
		}
	}
}

//Intent: Update key state
//Pre: key managing array
//Post: update key array
void Game::keyUpdate(bool key[]) {
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w':
		key[ValidInput::EW] = true;
		break;
	case 's':
		key[ValidInput::ES] = true;
		break;
	case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'd':
		key[ValidInput::ED] = true;
		break;
	case ' ':
		key[ValidInput::ESPACE] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	case '1':
		key[ValidInput::ESave] = true;
		break;
	case '2':
		key[ValidInput::ELoad] = true;
		break;
	default:
		break;
	}
}

//Intent: Update all characters' states
//Pre: key array
//Post: Update all characters' states
void Game::update(bool key[]) {
	try {
		// Clear Screen
		system("CLS");

		Position delta;

		// Check Input State
		bool hasInput = false;
		if (key[ValidInput::EW]) {
			delta -= Position(0, 1);
			hasInput = true;
		}
		else if (key[ValidInput::ES]) {
			delta += Position(0, 1);
			hasInput = true;
		}
		else if (key[ValidInput::EA]) {
			delta = delta - Position(1, 0);
			hasInput = true;
		}
		else if (key[ValidInput::ED]) {
			delta = delta + Position(1, 0);
			hasInput = true;
		}
		else {
			bool allInvalid = true;
			for (int i = 0; i < ValidInput::INVALID; i++) {
				if (key[i]) {
					allInvalid = false;
					break;
				}
			}

			//Exception Handling
			if (allInvalid) {
				throw invalid_argument("Invalid Input");

				/*std::cout << "invalid input\n";*/
			}
		}

		if (hasInput) {
			gHero.move(delta, gBoard);
		}

		// Manipulate update of two items using while loop
		for (int i = 0; i < gItems.size(); i++) {
			gItems[i]->update(gHero);
		}

		for (int i = 0; i < gCreatures.size(); i++) {
			gCreatures[i]->update(gHero, gBoard);
		}

		/*draw();
		drawInfo();*/
	}
	catch (const exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	draw();
	drawInfo();
}

//Intent: wall generation
//Pre: board, starting position, board width & height
//Post: board generated
void Game::wallGenerate(char** board, int xStart, int yStart, int width, int height) {
	if (width < 5 || height < 5) return;

	int xDiv = xStart + rand() % (width - 4) + 2;
	int yDiv = yStart + rand() % (height - 4) + 2;

	for (int i = 0; i < height; i++)
		if (i != yDiv) board[yStart + i][xDiv] = WALL;
	for (int i = 0; i < width; i++)
		if (i != xDiv) board[yDiv][xStart + i] = WALL;

	int doors[4] = { yStart + 1, yStart + height - 2, xStart + 1, xStart + width - 2 };

	if (yDiv - yStart - 1 > 0)
		doors[0] = yStart + rand() % (yDiv - yStart - 1) + 1;
	if (yStart + height - yDiv - 3 > 0)
		doors[1] = yDiv + 1 + rand() % (yStart + height - yDiv - 3);
	if (xDiv - xStart - 1 > 0)
		doors[2] = xStart + rand() % (xDiv - xStart - 1) + 1;
	if (xStart + width - xDiv - 3 > 0)
		doors[3] = xDiv + 1 + rand() % (xStart + width - xDiv - 3);

	board[doors[0]][xDiv] = ' '; // Up
	board[doors[1]][xDiv] = ' '; // Down
	board[yDiv][doors[2]] = ' '; // Left
	board[yDiv][doors[3]] = ' '; // Right

	wallGenerate(board, xStart, yStart, xDiv - xStart, yDiv - yStart); // top left
	wallGenerate(board, xDiv + 1, yStart, width - xDiv + xStart - 1, yDiv - yStart); // top right
	wallGenerate(board, xStart, yDiv + 1, xDiv - xStart, height - yDiv + yStart - 1); // bottom left
	wallGenerate(board, xDiv + 1, yDiv + 1, width - xDiv + xStart - 1, height - yDiv + yStart - 1); // bottom right
}

//Intent: setup the game board
//Pre: int rowN, int colN
//Post: game board created
void Game::setupBoard(int rowN, int colN) {
	// Allocate & init game board using 2d dynamic array
	gBoard = new char* [rowN];
	for (int i = 0; i < rowN; i++) {
		gBoard[i] = new char[colN];
		for (int j = 0; j < colN; j++) {
			if (i == 0 || i == rowN - 1 || j == 0 || j == colN - 1)
				gBoard[i][j] = WALL;
			else
				gBoard[i][j] = NOTHING;
		}
	}

	/* Maze Wall Generation */
	wallGenerate(gBoard, 1, 1, colN - 2, rowN - 2);
	/************************************************************************/

	// Setup for (random) position of all elements and implementation of game board using 2d dynamic array
	// Elements has to be randomly generated within canvas
	std::vector<std::vector<bool>> validFlags(GHEIGHT);
	for (int i = 0; i < GHEIGHT; i++) {
		validFlags[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++) {
			validFlags[i][j] = (gBoard[i][j] != WALL);
		}
	}

	auto getRandomPos = [&rowN, &colN]() {
		return Position((int)(rand() % colN), (int)(rand() % rowN));
	};

	auto getValidRandomPos = [&validFlags, &getRandomPos]() {
		while (true) {
			Position pos = getRandomPos();
			if (validFlags[pos.y][pos.x]) {
				return pos;
			}
		}
	};

	Position hPos = getValidRandomPos();
	validFlags[hPos.y][hPos.x] = false;
	gHero.setPos(hPos);

	for (int i = 0; i < gCreatures.size(); i++) {
		Position cPos = getValidRandomPos();
		validFlags[cPos.y][cPos.x] = false;
		gCreatures[i]->setPos(cPos);
	}

	for (int i = 0; i < gItems.size(); i++) {
		Position tPos = getValidRandomPos();
		validFlags[tPos.y][tPos.x] = false;
		gItems[i]->setPos(tPos);
	}
}

//Intent: draw the game board
//Pre: None
//Post: game board printed on the screen
void Game::draw() {
	// Add the hero into the board
	// Setup and implementation of drawing board using 2d vector

	std::vector<std::vector<char>> drawBoard(GHEIGHT);

	for (int i = 0; i < GHEIGHT; i++) {
		drawBoard[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Draw two items using for loop on drawBoard
	for (int i = 0; i < gItems.size(); i++) {
		Position t = gItems[i]->getPos();
		drawBoard[t.y][t.x] = gItems[i]->getIcon();
	}

	for (int i = 0; i < gCreatures.size(); i++) {
		Position c = gCreatures[i]->getPos();
		drawBoard[c.y][c.x] = gCreatures[i]->getIcon();
	}

	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			std::cout << drawBoard[i][j]; //  output
		}
		std::cout << "\n";
	}
}

//Intent: Draw each character's info
//Pre: None
//Post: Info printed on console
void Game::drawInfo() {
	std::cout << "The hero is level " << gHero.getLevel() << "(" << gHero.getExp() << "/" << gHero.getMaxExp() << " to level up)" << std::endl;
	std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
	std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
	std::cout << "Every time you step on a trigger T, the hero gets 10 exp." << std::endl;
	std::cout << "(ESC) Exit (1) Save (2) Load" << std::endl;
}

//Intent: Save current game data
//Pre: None
//Post: Game data saved in a text file
void Game::saveMap() {
	// Save dungen to file
	system("CLS");
	std::cout << "Input file name for saving or Exit to leave saving." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)
		return;

	std::ofstream oStream(input + ".txt");

	//Exception handling
	if (!oStream.is_open()) {
		throw runtime_error("Failed to open the output file.");
	}

	oStream << GWIDTH << " " << GHEIGHT << std::endl;

	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			oStream << gBoard[i][j];
		}
		oStream << std::endl;
	}
	oStream << std::endl;

	oStream << gHero.getPos() << " " << gHero.getHP() << " " << gHero.getLevel() << " " << gHero.getExp() << " " << gHero.getMaxExp() << std::endl;

	oStream << gCreatures.size() << std::endl;
	for (int i = 0; i < gCreatures.size(); i++) {
		oStream << gCreatures[i]->getIcon() << " " << gCreatures[i]->getPos() << endl;
	}

	oStream << gItems.size() << std::endl;

	for (int i = 0; i < gItems.size(); i++) {
		oStream << gItems[i]->getIcon() << " " << gItems[i]->getPos() << std::endl;
	}

	oStream.close();
}

//Intent: Load game data from file
//Pre: None
//Post: Game reset
void Game::loadMap() {
	// Load from file and reset the dungen
	system("CLS");
	std::cout << "Input file name for loading or Exit to leave loading." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)
		return;

	std::ifstream iStream(input + ".txt");

	//Exception Handling
	if (!iStream.is_open()) {
		throw std::runtime_error("Failed to open the input file.");
	}
	//if (!iStream.is_open())
	//	return;

	// reset dungen
	for (int i = 0; i < GHEIGHT; i++) {
		delete[] gBoard[i];
	}
	delete[] gBoard;

	for (int i = 0; i < gCreatures.size(); i++) {
		delete gCreatures[i];
	}
	gCreatures.clear();

	for (int i = 0; i < gItems.size(); i++) {
		delete gItems[i];
	}
	gItems.clear();

	iStream >> GWIDTH >> GHEIGHT;

	char _c;
	iStream.get(_c);

	gBoard = new char* [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++) {
		gBoard[i] = new char[GWIDTH];
		for (int j = 0; j < GWIDTH; j++) {
			iStream.get(gBoard[i][j]);
		}
		iStream.get(_c);
	}

	Position pos;
	int hp, level, exp, maxExp;
	iStream >> pos >> hp >> level >> exp >> maxExp;

	gHero.setPos(pos);
	gHero.setHP(hp);
	gHero.setLevel(level);
	gHero.setExp(exp);
	gHero.SetMaxExp(maxExp);

	int creatureN;
	iStream >> creatureN;

	char cIcons; //creatures' icon
	for (int i = 0; i < creatureN; i++) {
		iStream >> cIcons >> pos;
		//Creature
		if (cIcons == 'C' || cIcons == '!') {
			Creature* creature = new Creature();
			creature->setPos(pos);
			gCreatures.push_back(creature);
		}

		//Bug
		if (cIcons == 'B') {
			Bug* bug = new Bug();
			bug->setPos(pos);
			gCreatures.push_back(bug);
		}
	}

	int itemN;
	iStream >> itemN;

	char icons;
	for (int i = 0; i < itemN; i++) {
		iStream >> icons >> pos;
		//Trigger
		if (icons == 'T') {
			// Trigger* trigger = new Trigger();
			Item* trigger = new Trigger();
			trigger->setPos(pos);
			gItems.push_back(trigger);
		}

		//Snare
		if (icons == 'S') {
			// Snare* trigger = new Snare();
			Item* snare = new Snare();
			snare->setPos(pos);
			gItems.push_back(snare);
		}
	}

	iStream.close();
}
