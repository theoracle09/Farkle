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

	// Getters and Setters
	void setNumPlayers(int numPlayers);
	int getNumPlayers() const { return numPlayers_; };


private:
	Menu menu_;
	int numPlayers_;
};

