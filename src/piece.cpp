#include <bitset>
#include <string.h>
#include <ctype.h>
#include <iostream>

#include "Headers/piece.h"

using namespace std;

Piece::Piece(){
    whitePawn = bitset<64>( string("0000000000000000000000000000000000000000000000001111111100000000"));
    whiteKnight = bitset<64>( string("0000000000000000000000000000000000000000000000000000000001000010"));
    whiteBishop = bitset<64>( string("0000000000000000000000000000000000000000000000000000000000100100"));
    whiteRook = bitset<64>( string("0000000000000000000000000000000000000000000000000000000010000001"));
    whiteQueen = bitset<64>( string("0000000000000000000000000000000000000000000000000000000000001000"));
    whiteKing = bitset<64>( string("0000000000000000000000000000000000000000000000000000000000010000"));
    blackPawn = bitset<64>( string("0000000011111111000000000000000000000000000000000000000000000000"));
    blackKnight = bitset<64>( string("0100001000000000000000000000000000000000000000000000000000000000"));
    blackBishop = bitset<64>( string("0010010000000000000000000000000000000000000000000000000000000000"));
    blackRook = bitset<64>( string("1000000100000000000000000000000000000000000000000000000000000000"));
    blackQueen = bitset<64>( string("0000100000000000000000000000000000000000000000000000000000000000"));
    blackKing = bitset<64>( string("0001000000000000000000000000000000000000000000000000000000000000"));
}

void Piece::parseFen(string fen){
    int length = fen.length();

    for(int i=0; i<length; i++){
        switch (fen[i])
        {
        case 'r':
            this->blackRook.set(i);
            break;
        
        case 'n':
            this->blackKnight.set(i);
            break;
        
        case 'b':
            this->blackBishop.set(i);
            break;
        
        case 'q':
            this->blackQueen.set(i);
            break;
        
        case 'k':
            this->blackKing.set(i);
            break;

        case 'p':
            this->blackPawn.set(i);
            break;
        
        case 'R':
            this->blackRook.set(i);
            break;
        
        case 'N':
            this->blackKnight.set(i);
            break;
        
        case 'B':
            this->blackBishop.set(i);
            break;
        
        case 'Q':
            this->blackQueen.set(i);
            break;
        
        case 'K':
            this->blackKing.set(i);
            break;

        case 'P':
            this->blackPawn.set(i);
            break;


        default:
            if(isdigit(fen[i])){
                i += ((int)fen[i] - 1);
            }
        }
        
        cout << "i = " << i << endl;
    }
    this->boards->clear();
    this->boards->push_back(whitePawn);
    this->boards->push_back(whiteKnight);
    this->boards->push_back(whiteBishop);
    this->boards->push_back(whiteRook);
    this->boards->push_back(whiteQueen);
    this->boards->push_back(whiteKing);
    this->boards->push_back(blackPawn);
    this->boards->push_back(blackKnight);
    this->boards->push_back(blackBishop);
    this->boards->push_back(blackRook);
    this->boards->push_back(blackQueen);
    this->boards->push_back(blackKing);
}
