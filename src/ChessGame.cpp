#include <iostream>

#include "Headers/ChessGame.h"

ChessGame::ChessGame(): board(800, 800){

}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(board);
    
}