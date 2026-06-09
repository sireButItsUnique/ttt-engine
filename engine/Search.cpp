#include "Search.hpp"

int Search::rec(Board* board, int alpha, int beta, int ply, vector<vector<uint8_t>>& PV) {
    PV[ply].clear();
    
    int eval = board->eval();
    if (eval) return eval * (MATE - ply); // prefer faster wins and slower losses

    vector<int> moves;
    board->genMoves(moves);
    if (moves.empty()) return 0; // draw

    eval = -MATE; // assume opponent can win
    for (int move : moves) {
        Board newBoard = *board;
        newBoard.makeMove(move);
        int score = -rec(&newBoard, -beta, -alpha, ply + 1, PV); // negamax
        
        // Prune if move is too good -> opp has a better move last ply
        if (score >= beta) return score;
        
        if (score > alpha) {
            alpha = score;

            PV[ply].clear();
            PV[ply].push_back(move);

            // Copy PV to current PV
            if (ply + 1 < (int)PV.size()) {
                PV[ply].insert(PV[ply].end(), PV[ply+1].begin(), PV[ply+1].end());
            }
        }

        eval = max(eval, score);
    }

    return eval;
}
