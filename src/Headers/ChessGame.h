#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"
#include <string.h>

extern const int bishop_relevant_bits[64];
extern const int rook_relevant_bits[64];

class ChessGame: public sf::Drawable {
    public:
        // objects, vectors, enums
        Board board;

        // attributes
        BITBOARD pawn_attacks[2][64];
        BITBOARD knight_attacks[64];
        BITBOARD king_attacks[64];
        unsigned int random_state = 1804289383;      // state determined by random number generator

        // methods
        unsigned int get_random_U32_number();
        BITBOARD get_random_U64_number();
        BITBOARD get_random_magic_number();
        BITBOARD find_magic_number(int, int, int);
        void init_magic();
        BITBOARD generatePawnAttacks(int side, int square);
        BITBOARD generateKnightAttacks(int square);
        BITBOARD generateKingAttacks(int square);
        BITBOARD getBishopOccupancy(int square);
        BITBOARD getRookOccupancy(int square);
        BITBOARD generateBishopAttacks(int, BITBOARD);
        BITBOARD generateRookAttacks(int, BITBOARD);
        BITBOARD setOccupancies(int, int, BITBOARD);
        void init_leaper_attacks();

        int countBits(BITBOARD);
        int indexLeastSigBit(BITBOARD);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ChessGame(sf::RenderTarget& target);
        ChessGame(){};
        ~ChessGame(){};
};

#endif //CHESSGAME_H