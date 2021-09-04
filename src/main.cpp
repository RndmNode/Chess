#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <bitset>

#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

bool prevDragging = false;
bool prevMouseClicked = false;
bool dragging = false;
bool mouseClicked = false;

float mouseX = 0.0f;
float mouseY = 0.0f;

sf::Vector2f lastPosition;

Piece *selectedPiece;

sf::Vector2f traslateToSquare(sf::Vector2f pos, sf::RenderTarget &target){
    int x = pos.x;
    int y = pos.y;
    int windowX = target.getSize().x;
    int windowY = target.getSize().y;


}

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

            //if mouse moves, update coords
            if(event.type == sf::Event::MouseMoved){
                mouseX = event.mouseButton.x;
                mouseY = event.mouseButton.y;
            }
            
            // if left mouse button is pressed, drag piece
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                for(auto &i : chess.board.pieces){
                    if(i.m_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        mouseClicked = true;
                        dragging = true;
                        i.m_selected = true;
                        break;
                    }
                }
            }

            // if left mouse button is released, drop piece
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                for(auto &i : chess.board.pieces){
                    if(i.m_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
                        mouseClicked = false;
                        dragging = false;
                        //update selected piece?
                        lastPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                        break;
                    }
                }
            }
        }

        //dragging and dropping pieces//
        // if dragging
        if(dragging && mouseClicked){
            // loop through pieces to find selected and edit position
            // for(auto &i : chess.board.pieces){
            //     if(i.m_selected){
            //         i.m_sprite.setPosition(sf::Vector2f(mouseX,mouseY));
            //     }
            // }
            window.clear();
            window.display();
        }

        // if dropped
        if(!dragging && !mouseClicked){
            // loop through pieces to find selected and edit position
            // for(auto &i : chess.board.pieces){
            //     if(i.m_selected){
            //         i.m_sprite.setPosition(sf::Vector2f(lastPosition));
            //         i.m_selected = false;
            //     }
            // }
            window.clear();
            window.draw(chess);
            window.display();
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

