#pragma once
#include "includes.hpp"

namespace Move {
    // [0-1] is row
    // [2-3] is column
    // [4-7] is for piece type
    
    inline void setPos(uint8_t& move, int row, int col) {
        move |= (col << 2);
        move |= row;
    }

    inline void setPiece(uint8_t& move, int piece) {
        move |= (piece << 4);
    }

    inline int getRow(uint8_t move) {
        return (move & 0x03);
    }

    inline int getCol(uint8_t move) {
        return (move & 0x0C) >> 2;
    }

    inline int getPiece(uint8_t move) {
        return move  >> 4;
    }

    inline string toAlgebra(uint8_t move) {
        string map = " aAbBcC";
        string res = "(";
        res += map[getPiece(move)];
        res += ":";
        res += getRow(move) + '0';
        res += ", ";
        res += getCol(move) + '0';
        res += ")";
        return res;
    }
}