#include <bitset>
#include <iostream>

#include "Headers/Board.h"
#include "Headers/Piece.h"

using namespace std;

struct color{
    int r;
    int g;
    int b;
};
color light = {255, 248, 227}; //light squares
color dark = {122, 109, 94};   //dark squares


Board::Board(int width, int height){
    FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    // parseFen(FEN);

    loadBoard(width, height);
}

void Board::loadBoard(int width, int height){
    float rectX = (width / 8.0f);
    float rectY = (height / 8.0f);

    // setting square sizes equal to width & height / 8
    for(int i=0; i<64; i++){
        rectangles[i].setSize(sf::Vector2f(rectX, rectY));
    }

    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            color c = (file + rank) % 2 == 0 ? light : dark;
            rectangles[file + (rank*8)].setFillColor(sf::Color(c.r, c.g, c.b));
            rectangles[file + (rank*8)].setPosition(sf::Vector2f(rectX * file, rectY * rank));
        }
    }
}

// Temp debugging bitboard printer
void Board::printBoard(int board){
    std::cout << "\n\n";
    for(int rank=0; rank<8; rank++){
        for (int file=0; file<8; file++){
            std::cout << " " << bitboards[board][(rank * 8) + file] << " ";
        }
        std::cout << "\n";
    }
}

// void Board::parseFen(string fen){
//     //split out the position information from the FEN string
//     string pos = fen.substr(0,fen.find_first_of(' '));
//     int length = pos.length();

// }

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<64; i++){
        target.draw(rectangles[i]);
    }
}