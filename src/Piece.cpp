#include "Headers/Piece.h"

void Piece::toString(sf::Vector2f coordinates){
    //take in x & y positions to calculate algorithmic coordinates (e.g. 'b5') and store in piece.a_position

}

void Piece::setTexture(){
    a_sprite = sf::Sprite();
    sf::Texture tmpTexture;

    switch (a_type)
    {
    case 'P':
        tmpTexture.loadFromFile(a_player ? "include/pieces/white/Pawn.png" : "include/pieces/black/Pawn.png");
        a_sprite.setTexture(tmpTexture);
        break;
    
    default:
        break;
    }
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(a_sprite);
}