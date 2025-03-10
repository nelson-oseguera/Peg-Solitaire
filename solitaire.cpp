#include "solitaire.h"

// Default constructor: creates an empty object
Solitaire::Solitaire() : m_numRows(0), m_numColumns(0), m_board(nullptr), m_shape(NONE), m_numMarbles(0) { 
}

// Parameterized constructor: creates the specific board, allocates memory
Solitaire::Solitaire(BOARDSHAPE board) : m_shape(board) {
    if (m_shape == ENGLISH) {
        m_numRows = ENGLISHSIZE;
        m_numColumns = ENGLISHSIZE;
        m_numMarbles = NUMENGLISHMARBLES;
    } else if (m_shape == DIAMOND) {
        m_numRows = DIAMONDSIZE;
        m_numColumns = DIAMONDSIZE;
        m_numMarbles = NUMDIAMONDMARBLES;
    } else {
        // Unsupported shape, create an empty object
        m_numRows = 0;
        m_numColumns = 0;
        m_numMarbles = 0;
        m_board = nullptr;
        m_shape = NONE;  // Ensure board shape is set to NONE for unsupported shapes
        return;
    }

    // Allocate memory for the board only if it's a valid shape
    m_board = new int*[m_numRows];
    for (int i = 0; i < m_numRows; ++i) {
        m_board[i] = new int[m_numColumns];
    }

    // Initialize the board based on the shape
    if (m_shape == ENGLISH) {
        for (int i = 0; i < m_numRows; ++i) {
            for (int j = 0; j < m_numColumns; ++j) {
                if ((i < 2 || i > 4) && (j < 2 || j > 4)) {
                    m_board[i][j] = OUT;
                } else if (i == 3 && j == 3) {
                    m_board[i][j] = HOLE;
                } else {
                    m_board[i][j] = MARBLE;
                }
            }
        }
    } else if (m_shape == DIAMOND) {
        int mid = m_numRows / 2;
        for (int i = 0; i < m_numRows; ++i) {
            int start = abs(mid - i);
            int end = m_numColumns - start;
            for (int j = 0; j < m_numColumns; ++j) {
                if (j >= start && j < end) {
                    if (i == mid && j == mid) {
                        m_board[i][j] = HOLE;
                    } else {
                        m_board[i][j] = MARBLE;
                    }
                } else {
                    m_board[i][j] = OUT;
                }
            }
        }
    }
}

// Copy constructor: creates a deep copy of rhs
Solitaire::Solitaire(const Solitaire &rhs) : m_numRows(rhs.m_numRows), m_numColumns(rhs.m_numColumns), m_shape(rhs.m_shape), m_numMarbles(rhs.m_numMarbles) {
    if (rhs.m_board) {
        m_board = new int*[m_numRows];
        for (int i = 0; i < m_numRows; ++i) {
            m_board[i] = new int[m_numColumns];
            for (int j = 0; j < m_numColumns; ++j) {
                m_board[i][j] = rhs.m_board[i][j];
            }
        }
    } else {
        m_board = nullptr;
    }
}

// Destructor: deallocates memory
Solitaire::~Solitaire() {
    clear();
}

// Clears memory and reinitializes all members
void Solitaire::clear() {
    // Only clear the board, do not reset m_shape
    if (m_board != nullptr) {
        for (int i = 0; i < m_numRows; ++i) {
            delete[] m_board[i];
        }
        delete[] m_board;
        m_board = nullptr;  // Reset pointer after deleting memory
    }
    m_numRows = m_numColumns = m_numMarbles = 0;
    // m_shape is intentionally not modified here to retain the current board shape
}

// Reinitializes the game with the same board shape
bool Solitaire::newBoard() {
    if (m_shape == NONE) {
        // std::cout << "Error: Attempting to initialize a board with shape NONE." << std::endl;
        return false;  // Error case: do not reinitialize if the board shape is NONE
    }
    
    // Debugging: Check m_shape before clearing
    // std::cout << "Before clearing, m_shape is: " << m_shape << std::endl;

    // Clear the existing board only if it exists
    if (m_board != nullptr) {
        clear();
    }

    // Debugging: Check m_shape after clearing
    // std::cout << "After clearing, m_shape is: " << m_shape << std::endl;

    // Initialize board dimensions and marbles
    m_numMarbles = (m_shape == ENGLISH) ? NUMENGLISHMARBLES : (m_shape == DIAMOND) ? NUMDIAMONDMARBLES : 0;
    m_numRows = (m_shape == ENGLISH) ? ENGLISHSIZE : (m_shape == DIAMOND) ? DIAMONDSIZE : 0;
    m_numColumns = m_numRows;

    if (m_numRows == 0 || m_numColumns == 0) {
        std::cout << "Error: Invalid board dimensions for shape: " << m_shape << std::endl;
        return false;
    }

    // Allocate memory for the board
    m_board = new int*[m_numRows];
    for (int i = 0; i < m_numRows; ++i) {
        m_board[i] = new int[m_numColumns];
    }

    // Initialize the board based on the shape
    if (m_shape == ENGLISH) {
        for (int i = 0; i < m_numRows; ++i) {
            for (int j = 0; j < m_numColumns; ++j) {
                if ((i < 2 || i > 4) && (j < 2 || j > 4)) {
                    m_board[i][j] = OUT;
                } else if (i == 3 && j == 3) {
                    m_board[i][j] = HOLE;
                } else {
                    m_board[i][j] = MARBLE;
                }
            }
        }
    } else if (m_shape == DIAMOND) {
        int mid = m_numRows / 2;
        for (int i = 0; i < m_numRows; ++i) {
            int start = abs(mid - i);
            int end = m_numColumns - start;
            for (int j = 0; j < m_numColumns; ++j) {
                if (j >= start && j < end) {
                    if (i == mid && j == mid) {
                        m_board[i][j] = HOLE;
                    } else {
                        m_board[i][j] = MARBLE;
                    }
                } else {
                    m_board[i][j] = OUT;
                }
            }
        }
    }

    // std::cout << "Board successfully initialized for shape: " << m_shape << std::endl;
    return true;
}

void Solitaire::changeBoard(BOARDSHAPE board) {
    // std::cout << "Changing board. Current shape: " << m_shape << ", New shape: " << board << std::endl;

    if (board != m_shape) {
        clear();  // Clear the old board before changing to a new shape
        m_shape = board;  // Properly set the new shape
    }

    // Reinitialize the board after clearing or shape change
    if (!newBoard()) {
        std::cout << "Failed to initialize board for new shape: " << board << std::endl;
    }
}

// Makes a move
bool Solitaire::play(pair<int, int> origin, pair<int, int> destination) {
    int originX = origin.first;
    int originY = origin.second;
    int destX = destination.first;
    int destY = destination.second;

    if (originX < 0 || originX >= m_numRows || originY < 0 || originY >= m_numColumns ||
        destX < 0 || destX >= m_numRows || destY < 0 || destY >= m_numColumns) {
        return false; // Out of bounds
    }

    // Check if the move is orthogonal (i.e., horizontal or vertical)
    if (!((abs(originX - destX) == 2 && originY == destY) || (abs(originY - destY) == 2 && originX == destX))) {
        return false; // Not a valid orthogonal move
    }

    int midX = (originX + destX) / 2, midY = (originY + destY) / 2;

    if (m_board[originX][originY] != MARBLE || m_board[destX][destY] != HOLE || m_board[midX][midY] != MARBLE) {
        return false; // Invalid move
    }

    // Perform the move
    m_board[originX][originY] = HOLE;
    m_board[midX][midY] = HOLE;
    m_board[destX][destY] = MARBLE;
    --m_numMarbles;

    return true;
}

// Dumps the board for debugging purposes
void Solitaire::dumpBoard() {
    cout << "  ";
    for (int k = 0; k < m_numColumns; k++) {
        cout << k << " ";
    }
    cout << endl;
    for (int i = 1; i <= m_numRows; i++) {
        cout << i - 1 << " ";
        for (int j = 1; j <= m_numColumns; j++) {
            if (m_board[i - 1][j - 1] == OUT)
                cout << "  ";
            else if (m_board[i - 1][j - 1] == HOLE)
                cout << BLACKSTAR;
            else
                cout << REDSTAR;
        }
        cout << endl;
    }
    cout << endl;
}

// Reports the number of remaining marbles for debugging purposes
int Solitaire::reportNumMarbles() {
    cout << "You have " << m_numMarbles << " marbles to remove!" << endl;
    return m_numMarbles;
}