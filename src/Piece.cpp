#include <iostream>
#include "Headers/Piece.h"

Piece::Piece(char type, bool color){
    m_type = type;
    m_player = color;
}

void Piece::setTexture(){
    m_sprite = sf::Sprite();

    switch (m_type)
    {
    case 'P':
        m_sprite.setTexture(m_player ? PieceTextures::whitePawn : PieceTextures::blackPawn);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'N':
        m_sprite.setTexture(m_player ? PieceTextures::whiteKnight : PieceTextures::blackKnight);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'B':
        m_sprite.setTexture(m_player ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'R':
        m_sprite.setTexture(m_player ? PieceTextures::whiteRook : PieceTextures::blackRook);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'Q':
        m_sprite.setTexture(m_player ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
        m_sprite.setScale(1.6,1.6);
        break;
    case 'K':
        m_sprite.setTexture(m_player ? PieceTextures::whiteKing : PieceTextures::blackKing);
        m_sprite.setScale(1.6,1.6);
        break;

    default:
        std::cerr << "Error: piece does not exist.\n";
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