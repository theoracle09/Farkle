#pragma once
#include "Menu.h"
#include "Player.h"
#include <vector>

class GameManager
{
public:
	GameManager();
	void clearScreen();
	void displayMenu();
	void displayRules();
	void play();
	void pause(); // TODO Delete. OS specific function/code for testing

	// Getters and Setters
	void setNumPlayers(int numPlayers);


private:
	Menu menu_;
	int numPlayers_;
	std::vector<Player> players_;

	void recordPlayerName();
	int rollSingleDie();
};

