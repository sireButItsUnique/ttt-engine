#pragma once
#include "includes.hpp"
#include "helper.hpp"
#include "Board.hpp"

class Search {
public:
    static int rec(Board* board, int alpha, int beta, int ply, vector<vector<uint8_t>>& PV);
};