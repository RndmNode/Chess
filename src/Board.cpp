#include "Headers/Board.h"

struct color{
    int r;
    int g;
    int b;
};
color light = {255, 248, 227}; //light squares
color dark = {122, 109, 94};   //dark squares

//This fuction will display once at the beginning before placing pieces
// and ~should~ not have to be touched again
void Board::loadBoard(sf::RectangleShape rectangles[64], sf::Sprite sprites[16], int width, int height){
    float rectX = width / 8.0f;
    float rectY = height / 8.0f;

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
    for(int i=0; i<64; i++){
        switch (this->board[i])
        {
        case -1:
            textures[i].loadFromFile("include/pieces/black/Rook.png");
            break;
        
        case -2:
            textures[i].loadFromFile("include/pieces/black/Knight.png");
            break;
        
        case -3:
            textures[i].loadFromFile("include/pieces/black/Bishop.png");
            break;

        case -4:
            textures[i].loadFromFile("include/pieces/black/Queen.png");
            break;
        
        case -5:
            textures[i].loadFromFile("include/pieces/black/King.png");
            break;
        
        case -6:
            textures[i].loadFromFile("include/pieces/black/Pawn.png");
            break;

        case 1:
            textures[i].loadFromFile("include/pieces/white/Rook.png");
            break;
        
        case 2:
            textures[i].loadFromFile("include/pieces/white/Knight.png");
            break;
        
        case 3:
            textures[i].loadFromFile("include/pieces/white/Bishop.png");
            break;

        case 4:
            textures[i].loadFromFile("include/pieces/white/Queen.png");
            break;
        
        case 5:
            textures[i].loadFromFile("include/pieces/white/King.png");
            break;
        
        case 6:
            textures[i].loadFromFile("include/pieces/white/Pawn.png");
            break;

        default:
            break;
        }
    }
}