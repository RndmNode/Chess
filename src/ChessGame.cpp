#include <iostream>

#include "Headers/ChessGame.h"

ChessGame::ChessGame(sf::RenderTarget& target): board(target.getSize().x, target.getSize().y){

}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(board);
}