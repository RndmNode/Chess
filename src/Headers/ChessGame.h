#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"

class ChessGame: public sf::Drawable {
    private:
        // objects, vectors, enums
        Board board;

        // methods
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        ChessGame();
        ~ChessGame(){};
};

#endif //CHESSGAME_H