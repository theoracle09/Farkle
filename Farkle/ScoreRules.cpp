#include "stdafx.h"
#include "ScoreRules.h"
#include <algorithm> // std::sort
#include <vector>
#include <iostream>


ScoreRules::ScoreRules()
{
	
}

void ScoreRules::check(std::vector<int>& storedDice)
{
	// Check for triplets
	int count = 0;
	int triples = 0;
	std::vector<int> numberOfSides(6); // Need to define the size here, or we'll get vector subscript errors

	// Keeps a count of how many of each die the player has stored
	for (unsigned int i = 0; i < storedDice.size(); i++)
	{
		switch (storedDice[i])
		{
		case 1:
			++numberOfSides[0];
			break;
		case 2:
			++numberOfSides[1];
			break;
		case 3:
			++numberOfSides[2];
			break;
		case 4:
			++numberOfSides[3];
			break;
		case 5:
			++numberOfSides[4];
			break;
		case 6:
			++numberOfSides[5];
			break;

		}
	}

	// Create temp vector, and sort it to find the highest value
	std::vector<int> tempVector;

	for (unsigned int i = 0; i < numberOfSides.size(); i++)
	{
		tempVector.push_back(numberOfSides[i]);
	}
	
	// Sorts the vector in ascending order, so highest number is at index 5
	std::sort(tempVector.begin(), tempVector.end());

	// Find the value with the highest frequency
	for (unsigned int i = 0; i < numberOfSides.size(); i++)
	{
		if (tempVector[5] == numberOfSides[i])
		{
			std::cout << "\n\n\nTriplet: " << (i + 1);
			system("PAUSE");
		}
	}
}


