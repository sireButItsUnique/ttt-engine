#pragma once
#include "includes.hpp"
#include "helper.hpp"
#include "Move.hpp"

class Board {
public:
    uint8_t board[3][3]; // 0 for empty, 1/3/5 for a/b/c, 2/4/6 for A/B/C
    uint8_t pieces[7]; // how many pieces are left 
    bool turn; // false for player 1, true for player 2

    void init();

    /*
    * Generates all possible moves for current board and stores them in the given vector
    * @param moves vector to store the generated moves.
    */
    void genMoves(vector<int>& moves);
    
    /* 
    * Makes the given move on the board.
    * @param move the move to be made
    */
    void makeMove(int move);

    /*
    * Evaluates current board pos, 1 if cur turn wins, -1 if opp wins, 0 otherwise.
    */
    int eval();

    void setPos(string boardStr, string piecesStr, string turnStr);

    /*
    * Prints the current board state.
    */
    void print();
};