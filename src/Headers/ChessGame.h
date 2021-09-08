#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"

class ChessGame: public sf::Drawable {
    public:
        // objects, vectors, enums
        Board board;

        // methods
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ChessGame(sf::RenderTarget& target);
        ~ChessGame(){};
};

#endif //CHESSGAME_H