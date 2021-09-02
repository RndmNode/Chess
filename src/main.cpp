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

// FEN parsing debugger
void printFullCharBoard(Board board){
    char fullBoard[64];
    bool occupied;

    // loop through the squares
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            int square = (rank*8)+file;
            occupied = false;

            // loop through the boards to check bits
            for(int i=P; i<=k; i++){
                int bit = board.getBit(board.bitboards[i], square);
                if(bit == 1){
                    occupied = true;
                    fullBoard[square] = piece_to_char.at(i);
                    break;
                }
            }
            if(!occupied) fullBoard[square] = '.';
        }   
    }

    cout << "\nFull Board:\n ";
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            cout << fullBoard[(rank*8)+file];
        }
        cout << "\n ";
    }
}

int main(){
    game();

    return 0;
}

