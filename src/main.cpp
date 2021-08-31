#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

void game() {
    ChessGame chess;
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite sprite;

    texture.loadFromFile("include/pieces/black/Knight.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(1.6, 1.6);
    sprite.setPosition(100,100);

    sf::Vector2f pos = sf::Vector2f(800,800);

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
        window.draw(sprite);
        window.display();
    }
}

int main() {
    game();

    return 0;
}