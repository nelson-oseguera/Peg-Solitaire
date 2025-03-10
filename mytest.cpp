#include "solitaire.h"
#include <iostream>

using namespace std;

class Tester {
public:
    // Test the creation of an unsupported board (French board)
    bool testUnsupportedBoard() {
        Solitaire game(FRENCH);
        return game.m_shape == NONE && game.m_board == nullptr && game.m_numMarbles == 0;
    }

    // Test the creation of an English board
    bool testEnglishBoardCreation() {
        Solitaire game(ENGLISH);
        return game.m_shape == ENGLISH && game.m_numMarbles == NUMENGLISHMARBLES;
    }

    // Test the creation of a Diamond board
    bool testDiamondBoardCreation() {
        Solitaire game(DIAMOND);
        return game.m_shape == DIAMOND && game.m_numMarbles == NUMDIAMONDMARBLES;
    }

    // Test newBoard() for a normal case (reinitialize)
    bool testNewBoardNormalCase() {
        Solitaire game(ENGLISH);
        return game.newBoard() && game.m_numMarbles == NUMENGLISHMARBLES;
    }

    // Test newBoard() for an error case (empty object)
    bool testNewBoardErrorCase() {
        Solitaire game;
        return !game.newBoard();
    }

    // Test changeBoard() for the same board shape
    bool testChangeBoardSameShape() {
        Solitaire game(ENGLISH);
        game.changeBoard(ENGLISH);
        return game.m_shape == ENGLISH && game.m_numMarbles == NUMENGLISHMARBLES;
    }

    // Test changeBoard() for a different board shape
    bool testChangeBoardDifferentShape() {
        Solitaire game(ENGLISH);
        game.changeBoard(DIAMOND);
        return game.m_shape == DIAMOND && game.m_numMarbles == NUMDIAMONDMARBLES;
    }

    // Test valid play on a board
    bool testValidPlay(Solitaire& game, pair<int, int> origin, pair<int, int> destination) {
        return game.play(origin, destination);
    }

    // Test invalid play on a board
    bool testInvalidPlay(Solitaire& game, pair<int, int> origin, pair<int, int> destination) {
        return !game.play(origin, destination);
    }

    // Test copy constructor for a normal case
    bool testCopyConstructorNormalCase() {
        Solitaire game(DIAMOND);
        game.play({6, 4}, {4, 4});
        game.play({6, 6}, {6, 4});

        Solitaire copyGame(game);
        return game.m_numColumns == copyGame.m_numColumns &&
               game.m_numRows == copyGame.m_numRows &&
               game.m_shape == copyGame.m_shape &&
               game.m_numMarbles == copyGame.m_numMarbles &&
               game.m_board != copyGame.m_board;  // Ensure deep copy
    }

    // Test copy constructor for an empty object (error case)
    bool testCopyConstructorErrorCase() {
        Solitaire emptyGame;
        Solitaire copiedEmptyGame(emptyGame);
        return copiedEmptyGame.m_shape == NONE && copiedEmptyGame.m_board == nullptr && copiedEmptyGame.m_numMarbles == 0;
    }
};

int main() {
    Tester tester;

    // Run the full set of tests for English and Diamond boards

    // Test unsupported board
    cout << "Testing unsupported board: " << (tester.testUnsupportedBoard() ? "Passed" : "Failed") << endl;

    // Test English board creation and functionality
    cout << "Testing English board creation: " << (tester.testEnglishBoardCreation() ? "Passed" : "Failed") << endl;
    cout << "Testing new English board (normal case): " << (tester.testNewBoardNormalCase() ? "Passed" : "Failed") << endl;
    cout << "Testing change English board (same shape): " << (tester.testChangeBoardSameShape() ? "Passed" : "Failed") << endl;

    // Test moves on English board
    Solitaire englishGame(ENGLISH);
    // Adjust valid move to a correct one on the English board
    cout << "Testing valid play on English board: " << (tester.testValidPlay(englishGame, {1, 3}, {3, 3}) ? "Passed" : "Failed") << endl;
    cout << "Testing invalid play on English board: " << (tester.testInvalidPlay(englishGame, {2, 3}, {0, 3}) ? "Passed" : "Failed") << endl;

    // Test Diamond board creation and functionality
    cout << "Testing Diamond board creation: " << (tester.testDiamondBoardCreation() ? "Passed" : "Failed") << endl;
    cout << "Testing change board (different shape to Diamond): " << (tester.testChangeBoardDifferentShape() ? "Passed" : "Failed") << endl;

    // Test moves on Diamond board
    Solitaire diamondGame(DIAMOND);
    cout << "Testing valid play on Diamond board: " << (tester.testValidPlay(diamondGame, {6, 4}, {4, 4}) ? "Passed" : "Failed") << endl;
    cout << "Testing invalid play on Diamond board: " << (tester.testInvalidPlay(diamondGame, {6, 4}, {2, 4}) ? "Passed" : "Failed") << endl;

    // Test copy constructor for both boards
    cout << "Testing copy constructor (normal case on Diamond): " << (tester.testCopyConstructorNormalCase() ? "Passed" : "Failed") << endl;
    cout << "Testing copy constructor (error case): " << (tester.testCopyConstructorErrorCase() ? "Passed" : "Failed") << endl;

    return 0;
}