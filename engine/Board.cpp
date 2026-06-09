#include "Board.hpp"

void Board::init() {
    memset(board, 0, sizeof(board));
    for (int i = 0; i <= 6; i++) {
        pieces[i] = 2;
    }
    turn = p1;
}

void Board::setPos(string boardStr, string piecesStr, string turnStr) {
    int charToPiece[128];
    charToPiece['x'] = 0;
    charToPiece['a'] = 1;
    charToPiece['A'] = 2;
    charToPiece['b'] = 3;
    charToPiece['B'] = 4;
    charToPiece['c'] = 5;
    charToPiece['C'] = 6;
    
    // Set up the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char cur = boardStr[i * 4 + j];
            board[i][j] = charToPiece[cur];
        }
    }

    // Set up pieces left
    for (int i = 1; i <= 6; i++) {
        pieces[i] = piecesStr[i - 1] - '0';
    }

    // Set up turn
    turn = (turnStr == "1") ? p1 : p2;
}

void Board::genMoves(vector<int>& moves) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            uint8_t cur = board[i][j];

            uint8_t pos = 0;
            Move::setPos(pos, i, j);
            
            for (int piece = 1 + turn; piece <= 6; piece += 2) {
                if (ceil(piece / 2.0f) > ceil(cur / 2.0f) && pieces[piece] > 0) { // can overpower && have pieces left
                    uint8_t move = pos;
                    Move::setPiece(move, piece);
                    moves.push_back(move);
                }
            }
        }
    }
}

void Board::makeMove(int move) {
    int row = Move::getRow(move);
    int col = Move::getCol(move);
    int piece = Move::getPiece(move);

    board[row][col] = piece;
    pieces[piece]--;
    turn = !turn;
}

int Board::eval() {
    // conv to 1 for p1 pieces and -1 for p2 pieces to simplify eval
    int plrBoard[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j]) {
                if (board[i][j] % 2) {
                    plrBoard[i][j] = 1; // p1 piece
                } else {
                    plrBoard[i][j] = -1; // p2 piece
                }
            }
        }
    }

    // flip if it's p2's turn to eval from their perspective
    if (turn == p2) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                plrBoard[i][j] *= -1;
            }
        }
    }

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (plrBoard[i][0] && plrBoard[i][0] == plrBoard[i][1] && plrBoard[i][1] == plrBoard[i][2]) {
            return plrBoard[i][0];
        }
        if (plrBoard[0][i] && plrBoard[0][i] == plrBoard[1][i] && plrBoard[1][i] == plrBoard[2][i]) {
            return plrBoard[0][i];
        }
    }

    // Check diagonals
    if (plrBoard[0][0] && plrBoard[0][0] == plrBoard[1][1] && plrBoard[1][1] == plrBoard[2][2]) {
        return plrBoard[0][0];
    }
    if (plrBoard[0][2] && plrBoard[0][2] == plrBoard[1][1] && plrBoard[1][1] == plrBoard[2][0]) {
        return plrBoard[0][2];
    }

    return 0; // No winner
}

void Board::print() {
    string map = " aAbBcC";
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << map[board[i][j]] << " | ";
        }
        cout << endl << "+---+---+---+" << endl;
    }
    cout << "Pieces left: " << endl;
    cout << "Player 1: a: " << (int)pieces[1]
            << " b: " << (int)pieces[3]
            << " c: " << (int)pieces[5] << endl;
    cout << "Player 2: A: " << (int)pieces[2]
            << " B: " << (int)pieces[4]
            << " C: " << (int)pieces[6] << endl;
    cout << "Turn: Player " << (turn ? 2 : 1) << endl;
    
    string posStr = "xxx/xxx/xxx xxxxxx x";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j]) posStr[i * 4 + j] = map[board[i][j]];
        }
    }
    for (int i = 1; i <= 6; i++) {
        posStr[12 + i - 1] = pieces[i] + '0';
    }
    posStr[19] = turn ? '2' : '1';
    cout << "Pos: " << posStr << endl;
}