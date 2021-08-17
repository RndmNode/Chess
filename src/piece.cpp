#include <bitset>
#include <string.h>

#include "Headers/piece.h"

using namespace std;

Piece::Piece(){
    whitePawn = bitset<64>( string("0000000000000000000000000000000000000000000000001111111100000000"));
    whiteKnight;
    whiteBishop;
    whiteRook;
    whiteQueen;
    whiteKing;
    blackPawn = bitset<64>( string("0000000011111111000000000000000000000000000000000000000000000000"));
    blackKnight;
    blackBishop;
    blackRook;
    blackQueen;
    blackKing;
}