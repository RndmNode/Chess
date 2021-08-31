#include <iostream>

#include "Headers/ChessGame.h"

ChessGame::ChessGame(): board(800, 800){

}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    Piece pieces[8];
    for(int i=0; i<8; i++){
        pieces[i] = Piece('N', false);
        pieces[i].setTexture();
        pieces[i].setPosition(sf::Vector2f(i*100, i*100));
    }
    
    target.draw(board);
    for(int i=0; i<8; i++){
        target.draw(pieces[i]);
    }
}