/*
 * A testing class for your JumblePuzzle class and its exception. A few unit
 * tests are provided but you will need to add some more.
 * The code also contains a simple function that allows you to play the game, and
 * another function that you can use to display the puzzle.  You should not need to
 * alter either of these supplied functions unless you wish to enhance them without
 * changing the way JumblePuzzle operates.
 *
 * Edited by Alex Richardson
 * 0601 7909
 * 8acr1
 * CISC320 - Assignment #4
 */
#include <string>
#include <iostream>
#include <ctime>
#include "jumble.h"
using namespace std;

typedef char* charArrayPtr;

// Displays the puzzle to the screen.
// Row and column numbers are added to the display.
void showJumble(const charArrayPtr* jumble, const int size)
{
	int i, j;
	cout << "\n  ";
	for (i = 0; i < size; i++)
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
	cout << endl;
	for (i = 0; i < size; i++)
	{
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
		for (j = 0; j < size; j++)
			cout << jumble[i][j] << "  ";
		cout << endl;
	}
	cout << endl;

} // end showJumble

// How quickly can you find the hidden string?
void playGame()
{
	string toHide;
	string difficulty;
	int guessRow, guessCol;
	int start, finish;
	char guessDirection;

	cout << "Provide a string to hide in the puzzle, all lower case: ";
	cin >> toHide;
	cout << "\nChoose your difficulty level: \"easy\", \"medium\" or \"hard\": ";
	cin >> difficulty;

	JumblePuzzle* jp;
	try
	{
		jp = new JumblePuzzle(toHide, difficulty);
	}
	catch (BadJumbleException& e)
	{
		cerr << e.what();
		return;
	}

	showJumble(jp->getJumble(), jp->getSize());

	start = static_cast<int>(time(NULL));
	cout << "Enter row location: ";
	cin >> guessRow;
	cout << "Enter column location: ";
	cin >> guessCol;
	cout << "Enter direction (\"n\", \"e\", \"s\" or \"w\"): ";
	cin >> guessDirection;
	finish = static_cast<int>(time(NULL));
	if (guessRow == jp->getRowPos() && guessCol == jp->getColPos() &&
			guessDirection == jp->getDirection())
		cout << "You found it!" << endl;
	else
	{
		cout << "Wrong location..." << endl;
		cout << "The location is row: " << jp->getRowPos() << " col: " << jp->getColPos()
																		<< ", direction: " << jp->getDirection() << endl;
	}
	cout << "You took " << (finish - start) << " seconds." << endl;
	delete jp;
	jp = NULL;

} // end playGame

// Add unit tests to this function.  A few unit tests are provided to test your copy constructor,
// your assignment overloading and aliasing.  You need to write some more tests before these ones.
// Test the public members only ("Black Box Testing").  Test to make sure that exceptions are
// thrown when they should be, that the puzzle is the correct size and is formed properly, and
// that the accessors return what they should.  You can add these unit tests as you develop your
// code ("TDD") and comment out the supplied tests until you are ready for them.
void testJumble() {
	JumblePuzzle* jp;
	string hiddenWord = "HIDDEN";

	// Testing Accessors
	cout << "Testing Accessors: " << endl;
	jp = new JumblePuzzle(hiddenWord, "hard");

	char dir = jp->getDirection();
	if (dir != 'n' &&  dir != 'e' && dir != 's' && dir != 'w')
		cerr << "Direction Accessor returned invalid value." << endl;

	int size = jp->getSize();
	int correctSize = hiddenWord.size() * 4;
	if (correctSize != size)
		cerr << "Size Accessor returned invalid value." << endl;

	int row = jp->getRowPos();
	int col = jp->getColPos();

	if (row < 0 || row >= size)
		cerr << "Row Accessor returned invalid value." << endl;

	if (col < 0 || col >= size )
		cerr << "Column Accessor returned invalud value." << endl;

	cout << "Jumble Accessors working correctly." << endl;

	// Test puzzle is correct size
	cout << "\nTesting for correct puzzle size: " << endl;
	hiddenWord = "pie";
	correctSize = hiddenWord.size() * 2;
	jp = new JumblePuzzle(hiddenWord, "easy");

	if (jp->getSize() == correctSize)
		cout << "Correct puzzle size for easy difficulty." << endl;
	else
		cerr << "Invalid puzzle size for easy difficulty." << endl;

	correctSize = hiddenWord.size() * 3;
	jp = new JumblePuzzle(hiddenWord, "medium");

	if (jp->getSize() == correctSize)
		cout << "Correct puzzle size for medium difficulty." << endl;
	else
		cerr << "Invalid puzzle size for medium difficulty." << endl;

	correctSize = hiddenWord.size() * 4;
	jp = new JumblePuzzle(hiddenWord, "hard");

	if (jp->getSize() == correctSize)
		cout << "Correct puzzle size for hard difficulty." << endl;
	else
		cerr << "Invalid puzzle size for hard difficulty." << endl;

	// Puzzle Formed properly
	cout << "\nTesting for properly formed puzzle: " << endl;
	hiddenWord = "HIDDEN";
	jp = new JumblePuzzle(hiddenWord, "medium");
	row = jp->getRowPos();
	col = jp->getColPos();
	dir = jp->getDirection();
	charArrayPtr* jumble = jp->getJumble();

	if (jumble[row][col] != hiddenWord.at(0))
		cerr << "Invalid formation of puzzle. At row: " << row << ", col: " << col << ", direction: " << dir << endl;

	for (int i = 1; i < hiddenWord.size(); i++)
	{
		if (dir == 'n')
			row--;
		else if (dir == 'e')
			col++;
		else if (dir == 's')
			row++;
		else // dir == 'w'
			col--;

		if (jumble[row][col] != hiddenWord.at(i))
			cerr << "Invalid formation of puzzle. At row: " << row << ", col: " << col << ", direction: " << dir << endl;
	}

	cout << "Puzzle formed correctly." << endl;

	// Testing exceptions
	cout << "\nTesting Exceptions: " << endl;

	// Invalid word length
	try
	{
		jp = new JumblePuzzle("to", "easy");
	}
	catch (BadJumbleException& e)
	{
		cerr << e.what() << endl;
	}

	try
	{
		jp = new JumblePuzzle("aaaaaaaaaaa", "easy");
	}
	catch (BadJumbleException& e)
	{
		cerr << e.what() << endl;
	}

	// Invalid Difficulty
	try
	{
		jp = new JumblePuzzle("word", "Easy"); // Must be lower-case
	}
	catch (BadJumbleException& e)
	{
		cerr << e.what() << endl;
	}
	try
	{
		jp = new JumblePuzzle("word", "beginner"); // Must be easy, medium, or hard
	}
	catch (BadJumbleException& e)
	{
		cerr << e.what() << endl;
	}

	/*
	// Test copy constructor for proper operation
	cout << "Testing copy constructor:" << endl;
	// While debugging, you can use capital letters to make the hidden string easier to locate
	JumblePuzzle jp1("HELLO", "easy");
	showJumble(jp1.getJumble(), jp1.getSize());
	JumblePuzzle jp2(jp1);
	cout << "Should look the same:" << endl;
	showJumble(jp2.getJumble(), jp2.getSize());

	// Test aliasing from copy constructor
	charArrayPtr* puzzle = jp2.getJumble();
	int sz = jp2.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '.';
	cout << "Dotted diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 1:" << endl;
	showJumble(jp1.getJumble(), sz);
	cout << "Should be same as original 2:" << endl;
	showJumble(jp2.getJumble(), sz);

	// Test assignment operator for proper operation
	cout << "Testing assignment operator:" << endl;
	JumblePuzzle jp3("BYE", "easy");
	showJumble(jp3.getJumble(), jp3.getSize());
	JumblePuzzle jp4 = jp3;
	cout << "Should look the same:" << endl;
	showJumble(jp4.getJumble(), jp4.getSize());

	// Test aliasing from assignment operator
	puzzle = jp4.getJumble();
	sz = jp4.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '*';
	cout << "Star diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 3:" << endl;
	showJumble(jp3.getJumble(), sz);
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);


	// Test self-assignment
	jp4 = jp4;
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);
	*/
} // end testJumble

int main() {

	//testJumble();

	// Make sure your class works before you play the game!
	playGame();

	return 0;
} // end main
