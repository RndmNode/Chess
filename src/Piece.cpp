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
        originOffset = m_sprite.getOrigin();
        break;
    case B:
        m_sprite.setTexture(m_player ? PieceTextures::whiteBishop : PieceTextures::blackBishop);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        originOffset = m_sprite.getOrigin();
        break;
    case R:
        m_sprite.setTexture(m_player ? PieceTextures::whiteRook : PieceTextures::blackRook);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        originOffset = m_sprite.getOrigin();
        break;
    case Q:
        m_sprite.setTexture(m_player ? PieceTextures::whiteQueen : PieceTextures::blackQueen);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        originOffset = m_sprite.getOrigin();
        break;
    case K:
        m_sprite.setTexture(m_player ? PieceTextures::whiteKing : PieceTextures::blackKing);
        m_sprite.setScale(1.625,1.625);
        m_sprite.setOrigin(m_sprite.getLocalBounds().width/2,m_sprite.getLocalBounds().height/2);
        originOffset = m_sprite.getOrigin();
        break;

    default:
        std::cerr << "Error: piece does not exist.\n";
        break;
    }
}

void Piece::setPosition(sf::RenderTarget& target, sf::Vector2f coordinates){
    int windowX = target.getSize().x;
    int windowY = target.getSize().y;

    int side_x = windowX/8;
    int side_y = windowY/8;

    int x_boardPos = coordinates.x/side_x;
    int y_boardPos = coordinates.y/side_y;

    int x = (x_boardPos * side_x) + (side_x / 2);
    int y = (y_boardPos * side_y) + (side_y / 2);

    m_sprite.setPosition(x, y);
}

int Piece::getPosition(sf::RenderTarget& target, sf::Vector2f coordinates){
    int windowX = target.getSize().x;
    int windowY = target.getSize().y;

    int side_x = windowX/8;
    int side_y = windowY/8;

    int x_boardPos = coordinates.x/side_x;
    int y_boardPos = coordinates.y/side_y;

    return (y_boardPos * 8) + x_boardPos;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_sprite);
}