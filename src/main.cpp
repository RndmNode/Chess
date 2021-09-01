#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <bitset>

#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

void game() {
    ChessGame chess;
    sf::RenderWindow window;

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
        window.draw(chess);
        window.display();
    }
}

int main() {
    game();

    return 0;
}