#include "stdafx.h"
#include "Menu.h"
#include <fstream>  // File IO
#include <iostream> // Console IO
#include <string>


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
	std::string fileName = "FarkleRules.txt";

	std::ifstream inputFile;
	std::string fileRow;

	inputFile.open(fileName);

	if (!inputFile)
	{
		std::cout << "Unable to open " << fileName << "...\n";
		exit(1);
	}

	while (getline(inputFile, fileRow))
	{
		std::cout << fileRow << std::endl;
	}
}


