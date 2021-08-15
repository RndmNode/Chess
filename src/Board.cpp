#include <vector>

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
void Board::loadBoard(sf::RectangleShape rectangles[64], int width, int height){
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