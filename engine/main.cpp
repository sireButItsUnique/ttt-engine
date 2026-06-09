// position pos xxx/xcB/xxx 222112 1 
// position pos xxx/xcc/xxx 222102 2
// position pos axx/Bcc/xxx 122002 2

// position pos cCb/AcB/xxC 011000 1
// position pos xxx/xcx/xxx 222212 2
// position pos Cxx/xcx/xxx 222211 1

// position pos axx/xCx/xxC 222222 1

#include "includes.hpp"
#include "Board.hpp"
#include "Search.hpp"

void SPLIT_STRING(string s, vector<string>& tokens) {
    size_t pos = 0, found;
    while ((found = s.find_first_of(' ', pos)) != string::npos) {
        tokens.push_back(s.substr(pos, found - pos));
        pos = found + 1;
    }
    if (pos < s.size()) tokens.push_back(s.substr(pos));
}

int main() {
    Board board;
    board.init();

    string cmd;
    while (cin >> cmd) {
        if (cmd == "exit") return 0;
        if (cmd == "go") {
            getline(cin, cmd);
            vector<string> tokens;
            SPLIT_STRING(cmd, tokens);

            vector<vector<uint8_t>> PV(64); // PV for each ply
            int score = Search::rec(&board, -MATE, MATE, 0, PV);

            if (tokens.size() > 1 && tokens[1] == "d") {
                cout << "Score: " << score << endl << "Moves:\n";
                Board newBoard = board;
                for (int i = 0; i < PV[0].size(); i++) {
                    cout << to_string(i + 1) << ". " << Move::toAlgebra(PV[0][i]) << endl;
                    newBoard.makeMove(PV[0][i]);
                    newBoard.print();
                }
                cout << endl;
            } else {
                if (PV[0].empty()) cout << "bestmove (none) score " << score << endl;
                else cout << "bestmove " << Move::toAlgebra(PV[0][0]) << " score " << score << endl;
            }
            
        }
        if (cmd == "position") {
            getline(cin, cmd);
            vector<string> tokens;
            SPLIT_STRING(cmd, tokens);

            if (tokens[1] == "startpos") board.init();
            else if (tokens[1] == "pos") {
                cout << "Setting position with: " << tokens[2] << " " << tokens[3] << " " << tokens[4] << endl;
                board.setPos(tokens[2], tokens[3], tokens[4]);
            }
        }
        if (cmd == "d") {
            board.print();
        }
    }
    return 0;
}