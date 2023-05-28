#include "Game.h"

void Game::mainFlow() {
	srand(time(NULL));

	// keyboard state management
	bool gKeyState[ValidInput::INVALID];
	for (int i = 0; i < ValidInput::INVALID; i++) {
		gKeyState[i] = false;
	}

	while (true) {
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
	}

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
			saveMap();
			gKeyState[ValidInput::ESave] = false;
		}
		else if (gKeyState[ValidInput::ELoad]) {
			loadMap();
			gKeyState[ValidInput::ELoad] = false;
		}
	}
}

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

void Game::update(bool key[]) {
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
		if (allInvalid) {
			std::cout << "invalid input\n";
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

	draw();
	drawInfo();
}

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

void Game::drawInfo() {
	std::cout << "The hero is level " << gHero.getLevel() << "(" << gHero.getExp() << "/" << gHero.getMaxExp() << " to level up)" << std::endl;
	std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
	std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
	std::cout << "Every time you step on a trigger T, the hero gets 10 exp." << std::endl;
	std::cout << "(ESC) Exit (1) Save (2) Load" << std::endl;
}

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
	if (!iStream.is_open())
		return;

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