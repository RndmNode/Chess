#include <iostream>
#include "Headers/Piece.h"

Piece::Piece(char type, bool color){
    m_type = type;
    m_player = color;
}

// void Piece::toString(sf::Vector2f coordinates){
//     //take in x & y positions to calculate algorithmic coordinates (e.g. 'b5') and store in piece.a_position

// }

void Piece::setTexture(){
    m_sprite = sf::Sprite();
    sf::Texture tmpTexture;

    switch (m_type)
    {
    case 'P':
        if(!tmpTexture.loadFromFile(m_player ? "include/pieces/white/Pawn.png" : "include/pieces/black/Pawn.png")){
            std::cout << "Could not load texture..." << std::endl;
            break;
        }
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'N':
        if(!tmpTexture.loadFromFile(m_player ? "include/pieces/white/Knight.png" : "include/pieces/black/Knight.png")){
            std::cout << "Could not load texture..." << std::endl;
            break;
        }
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'B':
        if(!tmpTexture.loadFromFile(m_player ? "include/pieces/white/Bishop.png" : "include/pieces/black/Bishop.png")){
            std::cout << "Could not load texture..." << std::endl;
            break;
        }
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'R':
        if(!tmpTexture.loadFromFile(m_player ? "include/pieces/white/Rook.png" : "include/pieces/black/Rook.png")){
            std::cout << "Could not load texture..." << std::endl;
            break;
        }
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'Q':
        if(!tmpTexture.loadFromFile(m_player ? "include/pieces/white/Queen.png" : "include/pieces/black/Queen.png")){
            std::cout << "Could not load texture..." << std::endl;
            break;
        }
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'K':
        if(!tmpTexture.loadFromFile(m_player ? "include/pieces/white/King.png" : "include/pieces/black/King.png")){
            std::cout << "Could not load texture..." << std::endl;
            break;
        }
        tmpTexture.setSmooth(true);
        m_sprite.setTexture(tmpTexture);
        m_sprite.setScale(1.6,1.6);
        break;

    default:
        break;
    }
}

void Piece::setPosition(sf::Vector2f coordinates){
    sf::Vector2f pos = sf::Vector2f(coordinates.x, coordinates.y);
    m_sprite.setPosition(pos);
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}