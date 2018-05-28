#pragma once
#include "Menu.h"
#include "Player.h"
#include <vector>
#include <iostream>

class GameManager
{
public:
	GameManager();
	void displayMenu();
	void displayRules();
	void play();

	// Custom function to sort player vector based on who got the highst single dice roll
	static bool cmd(const Player& p1, const Player& p2) { return p1.getSingleDieRoll() > p2.getSingleDieRoll(); };

	// Getters and Setters


private:
	Menu menu_;
	int numPlayers_;
	int diceSides_; // Stores how many sides the dice have. Possible feature in the future.
	std::vector<Player> players_;
	Player winner_;
	
	void recordPlayerName();
	void findWhoGoesFirst();
	int rollSingleDie();
	void endGame(Player winner);
	void lastRound();
	void clearScreen() const { std::cout << std::string(100, '\n'); };
	
	// DEV
	int dev_usersNames_ = 0;
};

