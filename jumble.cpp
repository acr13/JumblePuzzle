/*
 * jumble.cpp
 *
 * Implementation for Jumble & BadJumbleException classes.
 *
 * Alex Richardson
 * 0601 7909
 * 8acr1
 * CISC320 - Assignment #4
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jumble.h"

using namespace std;

// BadJumbleException implementation
BadJumbleException::BadJumbleException(const string& m) : message(m) { }
string& BadJumbleException::what() { return message; }

// Constructors
JumblePuzzle::JumblePuzzle(const string& toHide, const string& difficulty)
{
	size = toHide.length();

	// Error Checking
	if (size < 3 || size > 10)
	{
		throw BadJumbleException("Invalid length of hidden word. Must be between 3 and 10 characters.");
	}

	if (difficulty == "easy")
		size *= 2;
	else if (difficulty == "medium")
		size *= 3;
	else if (difficulty == "hard")
		size *= 4;
	else
		throw BadJumbleException("Invalid difficulty. Must be \"easy\", \"medium\", or \"hard\".");

	jumble = new char*[size];

	// Create individual arrays on the heap
	for (int i = 0; i < size; i++)
		jumble[i] = new char[size];

	const char* letters = "abcdefghijklmnopqrstuvwxyz";

	// Fill the jumble with random letters

	srand(time(NULL));

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			jumble[i][j] = (char) letters[rand() % 25];

	// Hide the word
	row = rand() % size;
	col = rand() % size;

	// Put the first letter down
	jumble[row][col] = toHide.at(0);

	const char* dir = "nesw";
	bool placedWord = 0;

	while (!placedWord)
	{
		// Pick a random direction
		direction = dir [rand() % 4];

		if (direction == 'n')
		{
			// Place the remaining characters going upwards
			for (int i = 1; i < toHide.length(); i++)
			{
				// We're out of bounds, try another direction
				if ((row-i) < 0)
					break;
				else if (i == (toHide.length() - 1)) // final letter of word
				{
					jumble[row-i][col] = toHide.at(i);
					placedWord = 1;
				}
				else
					jumble[row-i][col] = toHide.at(i);
			}
		}
		else if (direction == 'e')
		{
			// East (to the right)
			for (int i = 1; i < toHide.length(); i++)
			{
				if ((col+i) > (size-1))
					break;
				else if (i == (toHide.length() - 1))
				{
					jumble[row][col+i] = toHide.at(i);
					placedWord = 1;
				}
				else
					jumble[row][col+i] = toHide.at(i);
			}
		}
		else if (direction == 's')
		{
			// Going downwards
			for (int i = 1; i < toHide.length(); i++)
			{
				if ((row+i) > (size-1))
					break;
				else if (i == (toHide.length() - 1))
				{
					jumble[row+i][col] = toHide.at(i);
					placedWord = 1;
				}
				else
					jumble[row+i][col] = toHide.at(i);
			}
		}
		else // direction == 'w'
		{
			// Going left (backwards)
			for (int i = 1; i < toHide.length(); i++)
			{
				if ( (col-i) < 0 )
					break;
				else if (i == (toHide.length() - 1))
				{
					jumble[row][col-i] = toHide.at(i);
					placedWord = 1;
				}
				else
					jumble[row][col-i] = toHide.at(i);
			}
		}
	}
}

// Copy Constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle& right)
{
	size = right.getSize();
	row = right.getRowPos();
	col = right.getColPos();
	direction = right.getDirection();

	jumble = new char*[size];

	// Create individual arrays on the heap
	for (int i = 0; i < size; i++)
		jumble[i] = new char[size];

	charArrayPtr* rightJumble = right.getJumble();

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			jumble[i][j] = rightJumble[i][j];
	}
}

// Assignment Overloading
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& right)
{
	if (this != &right) // make sure we dont assign to ourself
	{
		row = right.getRowPos();
		col = right.getColPos();
		direction = right.getDirection();
		size = right.getSize();

		// Delete old Jumble
		for (int i = 0; i < size; i++)
			delete[] jumble[i];
		delete[] jumble;

		// Copy new jumble over
		jumble = new char*[size];

		// Create individual arrays on the heap
		for (int i = 0; i < size; i++)
			jumble[i] = new char[size];

		charArrayPtr* rightJumble = right.getJumble();

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				jumble[i][j] = rightJumble[i][j];
		}

	}
	return *this;
}

// Destructor
JumblePuzzle::~JumblePuzzle()
{
	for (int i = 0; i < size; i++)
		delete jumble[i];

	delete[] jumble;
}


// JumblePuzzle Accessors
charArrayPtr* JumblePuzzle::getJumble() const
{
	charArrayPtr* newJumble = new char*[size];

	for (int i = 0; i < size; i++)
		newJumble[i] = new char[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			newJumble[i][j] = jumble[i][j];
	}

	return newJumble;
}

int JumblePuzzle::getSize() const { return size; }
int JumblePuzzle::getRowPos() const { return row; }
int JumblePuzzle::getColPos() const { return col; }
char JumblePuzzle::getDirection() const { return direction; }
