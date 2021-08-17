#ifndef PIECES_H
#define PIECES_H

using namespace std;

class Piece{
    public:
        Piece();
        bitset<64> whitePawn;
        bitset<64> whiteKnight;
        bitset<64> whiteBishop;
        bitset<64> whiteRook;
        bitset<64> whiteQueen;
        bitset<64> whiteKing;
        bitset<64> blackPawn;
        bitset<64> blackKnight;
        bitset<64> blackBishop;
        bitset<64> blackRook;
        bitset<64> blackQueen;
        bitset<64> blackKing;
        ~Piece(){};
};

#endif //PIECES_H