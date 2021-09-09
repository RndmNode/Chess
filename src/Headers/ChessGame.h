#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"

class ChessGame: public sf::Drawable {
    public:
        // objects, vectors, enums
        Board board;

        // attributes
        BITBOARD pawn_attacks[2][64];
        BITBOARD knight_attacks[64];
        BITBOARD king_attacks[64];

        // methods
        BITBOARD generatePawnAttacks(int side, int square);
        BITBOARD generateKnightAttacks(int square);
        BITBOARD generateKingAttacks(int square);
        BITBOARD getBishopOccupancy(int square);
        BITBOARD getRookOccupancy(int square);
        BITBOARD generateBishopAttacks(int, BITBOARD);
        BITBOARD generateRookAttacks(int, BITBOARD);
        void init_slider_attacks();
        void init_leaper_attacks();

        int countBits(BITBOARD);
        int indexLeastSigBit(BITBOARD);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ChessGame(sf::RenderTarget& target);
        ChessGame(){};
        ~ChessGame(){};
};

#endif //CHESSGAME_H