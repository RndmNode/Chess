#include <iostream>
#include <SFML/Graphics.hpp>
#include <bitset>
#include <string.h>
#include <vector>

#include "Headers/Board.h"

using namespace std;

int width = 800;
int height = 800;

void game() {
    sf::RenderWindow window;
    sf::RectangleShape rectangles[64];
    sf::Sprite sprites[16];
    
    Board board;
    board.loadBoard(rectangles, sprites, width, height);

    window.create(sf::VideoMode(width, height), "CHESS!");
    // run the program as long as the window is open
    while(window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while(window.pollEvent(event)){
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        for(int i=0; i<64; i++){
            window.draw(rectangles[i]);
        }
        window.display();
    }
}

int main() {
    //game();
    Board gameBoard;

    string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    gameBoard.parseFen(startingFEN);

    for(long unsigned int i=0; i<gameBoard.boards.size(); i++){
        cout << gameBoard.boardNames[i] << ": ";
        cout << gameBoard.boards[i].to_string() << endl;
    }

    return 0;
}