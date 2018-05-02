#include "stdafx.h"
#include "Menu.h"
#include <iostream>


Menu::Menu()
{
}

void Menu::printMainMenu()
{
	std::cout << "|------------------------------------------------------------|\n";
	std::cout << "|                                                            |\n";
	std::cout << "|                           FARKLE                           |\n";
	std::cout << "|                                                            |\n";
	std::cout << "|                                                            |\n";
	std::cout << "|                           Play                             |\n";
	std::cout << "|                           Rules                            |\n";
	std::cout << "|                           Exit                             |\n";
	std::cout << "|                                                            |\n";
	std::cout << "|------------------------------------------------------------|\n";
}

void Menu::printRules()
{
	std::cout << "Rules.\n";
}


