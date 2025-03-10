# Peg-Solitaire

This project is a C++ implementation of a Peg Solitaire game, supporting two board shapes: English and Diamond. It allows players to perform valid moves following the classical peg solitaire rules, with an object-oriented design. The code includes robust memory management, deep copy functionalities, and a comprehensive testing framework to ensure correctness of operations like board creation, movement, and copying.

Core Features
1. Board Shapes Supported
English Board (7x7 matrix, 32 marbles)
Diamond Board (9x9 matrix, 40 marbles)
Unsupported Board (French) is gracefully handled as an empty object.

2. Class Design (Solitaire Class)
Attributes:

m_board: 2D dynamically allocated array representing the board.
m_numRows, m_numColumns: Board dimensions.
m_numMarbles: Tracks number of marbles left.
m_shape: Enum for board shape (English, Diamond, or None).
Important Methods:

Solitaire(): Default constructor (empty board).
Solitaire(BOARDSHAPE): Parameterized constructor for specific board.
~Solitaire(): Destructor for safe memory deallocation.
Solitaire(const Solitaire&): Deep copy constructor.
clear(): Frees board memory and resets variables.
newBoard(): Reinitializes the current board shape.
changeBoard(BOARDSHAPE): Changes board shape and reinitializes.
play(origin, destination): Makes a move if valid.
dumpBoard(): Displays the board (for debugging).
reportNumMarbles(): Shows remaining marbles.

3. Game Logic and Movement
Moves are only valid if:
Move is orthogonal (horizontal/vertical, jumping exactly one marble).
Destination is an empty hole.
There is a marble between the origin and destination.
After a valid move:
Origin and jumped-over marble are emptied.
Destination holds a marble.
Marble count decreases.

4. Memory Safety
Full support for deep copying and destruction to avoid memory leaks:
Dynamic allocation/deallocation of 2D board.
Copy constructor ensures distinct copies.

5. Testing Framework (Tester Class)
Included is a Tester class with automated tests that validate:

Board creation (English, Diamond, Unsupported).
newBoard() normal and error cases.
changeBoard() for same/different shapes.
Valid and invalid moves.
Copy constructor correctness for both filled and empty objects.

Skills & Concepts Demonstrated
Object-Oriented Programming (OOP) in C++
Dynamic memory management and deep copying
Game logic implementation
Testing and validation of class methods
Enum usage and clear code structuring
