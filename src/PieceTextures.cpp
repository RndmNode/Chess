#include "Headers/PieceTextures.h"

sf::Texture PieceTextures::loadTexture(std::string str){
    sf::Texture tmp;
    if(!tmp.loadFromFile(str)){
        std::cout << "Error loading file: " << str << std::endl;
    }
    tmp.setSmooth(true);
    return tmp;
}

sf::Texture PieceTextures::whitePawn = PieceTextures::loadTexture("include/pieces/white/Pawn.png");
sf::Texture PieceTextures::whiteBishop = PieceTextures::loadTexture("include/pieces/white/Bishop.png");
sf::Texture PieceTextures::whiteKnight = PieceTextures::loadTexture("include/pieces/white/Knight.png");
sf::Texture PieceTextures::whiteRook = PieceTextures::loadTexture("include/pieces/white/Rook.png");
sf::Texture PieceTextures::whiteQueen = PieceTextures::loadTexture("include/pieces/white/Queen.png");
sf::Texture PieceTextures::whiteKing = PieceTextures::loadTexture("include/pieces/white/King.png");

sf::Texture PieceTextures::blackPawn = PieceTextures::loadTexture("include/pieces/black/Pawn.png");
sf::Texture PieceTextures::blackBishop = PieceTextures::loadTexture("include/pieces/black/Bishop.png");
sf::Texture PieceTextures::blackKnight = PieceTextures::loadTexture("include/pieces/black/Knight.png");
sf::Texture PieceTextures::blackRook = PieceTextures::loadTexture("include/pieces/black/Rook.png");
sf::Texture PieceTextures::blackQueen = PieceTextures::loadTexture("include/pieces/black/Queen.png");
sf::Texture PieceTextures::blackKing = PieceTextures::loadTexture("include/pieces/black/King.png");