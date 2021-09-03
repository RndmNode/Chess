#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <bitset>

#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

void game() {
    sf::RenderWindow window;

    window.create(sf::VideoMode(width, height), "CHESS!");
    ChessGame chess(window);
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
    // Board board(800,800);

    // char bBoard[64];

    // for(int i=0; i<12; i++){
    //     for(int rank=0; rank<8; rank++){
    //         for(int file=0; file<8; file++){
    //             if(board.bitboards[i][(rank*8)+file] == 1){
    //                 bBoard[(rank*8)+file] = piece_to_char.at(i);
    //                 bBoard[(rank*8)+file + 1] = ' ';
    //             }
    //         }
    //     }
    // }

    // cout << "\n\n";
    // for(int rank=0; rank<8; rank++){
    //     for(int file=0; file<8; file++){
    //         cout << bBoard[(rank*8)+file];
    //     }
    //     cout << "\n ";
    // }

    return 0;
}