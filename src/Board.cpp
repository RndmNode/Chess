#include <bitset>
#include <iostream>

#include "Headers/Board.h"

using namespace std;

struct color{
    int r;
    int g;
    int b;
};
color light = {255, 248, 227}; //light squares
color dark = {122, 109, 94};   //dark squares


// Not really sure if these bitsets are necessary at the moment...
Board::Board(){
    //Set board setting 64bit sets (boards)
    whiteSquares = bitset<64>( string("1010101001010101101010100101010110101010010101011010101001010101"));
    blackSquares = bitset<64>( string("0101010110101010010101011010101001010101101010100101010110101010"));
    whitePieces = bitset<64>( string("0000000000000000000000000000000000000000000000001111111111111111"));
    blackPieces = bitset<64>( string("1111111111111111000000000000000000000000000000000000000000000000"));
    occupiedSquares = bitset<64>( string("1111111111111111000000000000000000000000000000001111111111111111"));
    emptySquares = bitset<64>( string("0000000000000000111111111111111111111111111111110000000000000000"));

    //Set starting board Positions
    // whitePawn = bitset<64>( string("0000000000000000000000000000000000000000000000001111111100000000"));
    // whiteKnight = bitset<64>( string("0000000000000000000000000000000000000000000000000000000001000010"));
    // whiteBishop = bitset<64>( string("0000000000000000000000000000000000000000000000000000000000100100"));
    // whiteRook = bitset<64>( string("0000000000000000000000000000000000000000000000000000000010000001"));
    // whiteQueen = bitset<64>( string("0000000000000000000000000000000000000000000000000000000000001000"));
    // whiteKing = bitset<64>( string("0000000000000000000000000000000000000000000000000000000000010000"));
    // blackPawn = bitset<64>( string("0000000011111111000000000000000000000000000000000000000000000000"));
    // blackKnight = bitset<64>( string("0100001000000000000000000000000000000000000000000000000000000000"));
    // blackBishop = bitset<64>( string("0010010000000000000000000000000000000000000000000000000000000000"));
    // blackRook = bitset<64>( string("1000000100000000000000000000000000000000000000000000000000000000"));
    // blackQueen = bitset<64>( string("0000100000000000000000000000000000000000000000000000000000000000"));
    // blackKing = bitset<64>( string("0001000000000000000000000000000000000000000000000000000000000000"));
}

void Board::loadBoard(sf::RectangleShape rectangles[64], sf::Sprite sprites[16], int width, int height){
    float rectX = (width / 8.0f);
    float rectY = (height / 8.0f);

    // setting square sizes equal to width & height / 8
    for(int i=0; i<64; i++){
        rectangles[i].setSize(sf::Vector2f(rectX, rectY));
    }

    int counter = 0;
    for(int file=0; file<8; file++){
        for(int rank=0; rank<8; rank++){
            color c = (file + rank) % 2 == 0 ? light : dark;
            rectangles[counter].setFillColor(sf::Color(c.r, c.g, c.b));
            rectangles[counter].setPosition(sf::Vector2f(rectX * file, rectY * rank));
            counter++;
        }
    }
}

void Board::loadTextures(sf::Texture textures[64]){
    
}

void Board::parseFen(string fen){
    int length = fen.length();

    for(long unsigned int i=0; i<boards.size(); i++){
        boards[i].reset();
    }

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
            
        case '/':

            break;

        default:
            if(isdigit(fen[i])){
                i += ((int)fen[i] - 1);
            }
        }
        cout << "i = " << i << endl;
    }
    boards.clear();
    // boards.push_back(whitePawn);
    // boards.push_back(whiteKnight);
    // boards.push_back(whiteBishop);
    // boards.push_back(whiteQueen);
    // boards.push_back(whiteKing);
    // boards.push_back(whiteRook);
    boards.push_back(blackPawn);
    boards.push_back(blackKnight);
    boards.push_back(blackBishop);
    boards.push_back(blackRook);
    boards.push_back(blackQueen);
    boards.push_back(blackKing);

}