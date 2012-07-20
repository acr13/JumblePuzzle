/*
 * jumble.h
 *
 * Header file for Jumble & BadJumbleException classes.
 *
 * Alex Richardson
 */

#ifndef JUMBLE_H_
#define JUMBLE_H_

#include <string>

using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle
{
	public:
		// Constructors
		JumblePuzzle(const string&, const string&);
		JumblePuzzle(const JumblePuzzle&);

		// Destructor
		~JumblePuzzle();

		 // Overloaded Assignment Operator
		JumblePuzzle& operator=(const JumblePuzzle&);

		// Accessors
		charArrayPtr* getJumble() const;
		int getSize() const;
		int getRowPos() const;
		int getColPos() const;
		char getDirection() const;

	private:
		int size;
		int row;
		int col;
		char direction;
		charArrayPtr* jumble;
};

class BadJumbleException
{
	public:
		BadJumbleException(const string&); 							// Constructor with string error message
		string& what();												// Description of error.

	private:
		string message;
};

#endif /* JUMBLE_H_ */
