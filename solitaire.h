#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include <iostream>
#include <string>

using namespace std;

class Grader; // This class is for grading purposes, no need to do anything
class Tester; // This is your tester class, you add your test functions in this class

// ENGLISH board shape has 33 holes
// DIAMOND board shape has 41 holes
// We do not support FRENCH board
enum BOARDSHAPE { NONE, ENGLISH, FRENCH, DIAMOND };

const int ENGLISHSIZE = 7; // Used to create a 7x7 matrix
const int DIAMONDSIZE = 9; // Used to create a 9x9 matrix
const int NUMENGLISHMARBLES = 32; // Total number of marbles used on an English board
const int NUMDIAMONDMARBLES = 40; // Total number of marbles used on a Diamond board

const int OUT = 0;
const int HOLE = 1;
const int MARBLE = 2;

#define REDSTAR "\033[1;31m\u2731\033[0m " // Represents a marble (red bold asterisk)
#define BLACKSTAR "\u23E3 " // Represents a hole (BENZENE RING WITH CIRCLE)

class Solitaire {
public:
    friend class Grader;
    friend class Tester;

    Solitaire(); // Creates an empty object
    Solitaire(BOARDSHAPE board); // Creates the specific board, allocates memory
    Solitaire(const Solitaire &rhs); // Copy constructor
    ~Solitaire(); // Destructor

    void clear(); // Clears memory and reinitializes all members
    bool newBoard(); // Reinitializes the game with the same board shape
    void changeBoard(BOARDSHAPE board); // Creates a new board
    bool play(pair<int, int> origin, pair<int, int> destination); // Makes a move
    void dumpBoard(); // For debugging purposes
    int reportNumMarbles(); // For debugging purposes

private:
    int m_numRows;
    int m_numColumns;
    int **m_board; // The 2D structure to store the game
    BOARDSHAPE m_shape; // The board shape (either English or Diamond)
    int m_numMarbles; // Current number of marbles

    /******************************************
    * Private function declarations go here! *
    ******************************************/
};

#endif // SOLITAIRE_H