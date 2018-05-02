#pragma once
#include "Menu.h"

class GameManager
{
public:
	GameManager();
	void clearScreen();
	void displayMenu();
	void displayRules();
	void play();


private:
	Menu menu_;
	int numPlayers_;
};

