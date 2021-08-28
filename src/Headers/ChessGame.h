#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"

class ChessGame: public sf::Drawable {
    private:
        Board board;
        std::array<Piece, 16> whitePieces;
        std::array<Piece, 16> blackPieces;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        ChessGame();
        ~ChessGame(){};
};

#endif //CHESSGAME_H