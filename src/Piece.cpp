#include "Headers/Piece.h"

Piece::Piece(char type, bool color){
    m_type = type;
    m_player = color;

    setTexture();
}

void Piece::toString(sf::Vector2f coordinates){
    //take in x & y positions to calculate algorithmic coordinates (e.g. 'b5') and store in piece.a_position

}

void Piece::setTexture(){
    m_sprite = sf::Sprite();
    sf::Texture tmpTexture;

    switch (m_type)
    {
    case 'P':
        tmpTexture.loadFromFile(m_player ? "include/pieces/white/Pawn.png" : "include/pieces/black/Pawn.png");
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'N':
        tmpTexture.loadFromFile(m_player ? "include/pieces/white/Knight.png" : "include/pieces/black/Knight.png");
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'B':
        tmpTexture.loadFromFile(m_player ? "include/pieces/white/Bishop.png" : "include/pieces/black/Bishop.png");
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'R':
        tmpTexture.loadFromFile(m_player ? "include/pieces/white/Rook.png" : "include/pieces/black/Rook.png");
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'Q':
        tmpTexture.loadFromFile(m_player ? "include/pieces/white/Queen.png" : "include/pieces/black/Queen.png");
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'K':
        tmpTexture.loadFromFile(m_player ? "include/pieces/white/King.png" : "include/pieces/black/King.png");
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;

    default:
        break;
    }
}

void Piece::setPosition(sf::Vector2f coordinates){
    sf::Vector2f pos = sf::Vector2f(coordinates.x/8, coordinates.y/8);
    m_sprite.setPosition(pos);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}