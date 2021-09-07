#include <iostream>
#include "Headers/Board.h"

Piece::Piece(int type, bool color){
    m_type = type;
    m_player = color;
}

void Piece::setTexture(){
    m_sprite = sf::Sprite();

    switch (m_type)
    {
    case P:
        m_sprite.setTexture(m_player ? PieceTextures::whitePawn : PieceTextures::blackPawn);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        originOffset = m_sprite.getOrigin();
        break;
    case N:
        m_sprite.setTexture(m_player ? PieceTextures::whiteKnight : PieceTextures::blackKnight);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        break;
    case B:
        m_sprite.setTexture(m_player ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        break;
    case R:
        m_sprite.setTexture(m_player ? PieceTextures::whiteRook : PieceTextures::blackRook);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        break;
    case Q:
        m_sprite.setTexture(m_player ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        break;
    case K:
        m_sprite.setTexture(m_player ? PieceTextures::whiteKing : PieceTextures::blackKing);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        break;

    default:
        std::cerr << "Error: piece does not exist.\n";
        break;
    }
}

void Piece::setPosition(sf::RenderTarget& target, sf::Vector2f coordinates){
    int x = coordinates.x;
    int y = coordinates.y;
    int windowX = target.getSize().x;
    int windowY = target.getSize().y;
    int side_x = windowX/8;
    int side_y = windowY/8;

}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}