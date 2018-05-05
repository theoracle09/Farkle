#include "stdafx.h"
#include "Player.h"


Player::Player(std::string name)
{
	name_ = name;
	score_ = 0;
	singleDieRoll_ = 0;
	isFirstPlayer_ = false;
}

