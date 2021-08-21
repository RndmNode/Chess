#ifndef PIECES_H
#define PIECES_H

#include <bitset>
#include <vector>

typedef bitset<64> BOARD;

using namespace std;

class Piece{
    public:
        Piece();
        BOARD whitePawn;
        BOARD whiteKnight;
        BOARD whiteBishop;
        BOARD whiteRook;
        BOARD whiteQueen;
        BOARD whiteKing;
        BOARD blackPawn;
        BOARD blackKnight;
        BOARD blackBishop;
        BOARD blackRook;
        BOARD blackQueen;
        BOARD blackKing;

        vector<BOARD> boards[12];
        void parseFen(string fen);
        ~Piece(){};
};

#endif //PIECES_H