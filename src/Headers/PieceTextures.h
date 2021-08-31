#ifndef PIECETEXTURES_H
#define PIECETEXTURES_H 

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class PieceTextures{
    public:
        static sf::Texture whitePawn;
        static sf::Texture whiteBishop;
        static sf::Texture whiteKnight;
        static sf::Texture whiteRook;
        static sf::Texture whiteQueen;
        static sf::Texture whiteKing;

        static sf::Texture blackPawn;
        static sf::Texture blackBishop;
        static sf::Texture blackKnight;
        static sf::Texture blackRook;
        static sf::Texture blackQueen;
        static sf::Texture blackKing;

        static sf::Texture loadTexture(std::string str);
};

#endif //PIECETEXTURES_H