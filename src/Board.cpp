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


Board::Board(int width, int height){
    FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    parseFen(FEN);

    loadBoard(800, 800);
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

void Board::parseFen(string fen){
    //split out the position information from the FEN string
    string pos = fen.substr(0,fen.find_first_of(' '));
    int length = pos.length();

    int placeTracker = 0;

    for(long unsigned int i=0; i<whiteBoards.size(); i++){
        whiteBoards[i].reset();
        blackBoards[i].reset();
    }

    for(int i=0; i<length; i++){
        switch (fen[i])
        {
        case 'r':
            this->blackRook.set(placeTracker);
            placeTracker++;
            break;
        
        case 'n':
            this->blackKnight.set(placeTracker);
            placeTracker++;
            break;
        
        case 'b':
            this->blackBishop.set(placeTracker);
            placeTracker++;
            break;
        
        case 'q':
            this->blackQueen.set(placeTracker);
            placeTracker++;
            break;
        
        case 'k':
            this->blackKing.set(placeTracker);
            placeTracker++;
            break;

        case 'p':
            this->blackPawn.set(placeTracker);
            placeTracker++;
            break;
        
        case 'R':
            this->whiteRook.set(placeTracker);
            placeTracker++;
            break;
        
        case 'N':
            this->whiteKnight.set(placeTracker);
            placeTracker++;
            break;
        
        case 'B':
            this->whiteBishop.set(placeTracker);
            placeTracker++;
            break;
        
        case 'Q':
            this->whiteQueen.set(placeTracker);
            placeTracker++;
            break;
        
        case 'K':
            this->whiteKing.set(placeTracker);
            placeTracker++;
            break;

        case 'P':
            this->whitePawn.set(placeTracker);
            placeTracker++;
            break;

        case '/':
            continue;

        default:
            if(isdigit(fen[i])){
                placeTracker += (((int)fen[i] - '0'));
            }
        }
        
    }
    whiteBoards.clear();
    blackBoards.clear();

    whiteBoards.push_back(whitePawn);
    whiteBoards.push_back(whiteKnight);
    whiteBoards.push_back(whiteBishop);
    whiteBoards.push_back(whiteRook);
    whiteBoards.push_back(whiteQueen);
    whiteBoards.push_back(whiteKing);

    blackBoards.push_back(blackPawn);
    blackBoards.push_back(blackKnight);
    blackBoards.push_back(blackBishop);
    blackBoards.push_back(blackRook);
    blackBoards.push_back(blackQueen);
    blackBoards.push_back(blackKing);

}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<64; i++){
        target.draw(rectangles[i]);
    }
}