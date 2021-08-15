#include <iostream>
#include <SFML/Graphics.hpp>

#include "Board.h"

int width = 800;
int height = 800;

void game() {
    sf::RenderWindow window;
    sf::RectangleShape rectangles[64];
    
    Board board;
    board.loadBoard(rectangles, width, height);

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
    game();
    return 0;
}