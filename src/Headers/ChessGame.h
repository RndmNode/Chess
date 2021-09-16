#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"
#include <string.h>

extern const int bishop_relevant_bits[64];
extern const int rook_relevant_bits[64];

extern const BITBOARD rook_magic_numbers[64];
extern const BITBOARD bishop_magic_numbers[64];

extern BITBOARD pawn_attacks[2][64];
extern BITBOARD knight_attacks[64];
extern BITBOARD king_attacks[64];
extern BITBOARD bishop_masks[64];
extern BITBOARD rook_masks[64];
extern BITBOARD bishop_attacks[64][512];
extern BITBOARD rook_attacks[64][4096];
extern unsigned int random_state;

class ChessGame: public sf::Drawable {
    public:
        // objects, vectors, enums
        Board board;

        // attributes

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
        BITBOARD generateBishopAttacks_onTheFly(int, BITBOARD);
        BITBOARD generateRookAttacks_onTheFly(int, BITBOARD);
        BITBOARD setOccupancies(int, int, BITBOARD);
        BITBOARD get_Bishop_Attacks(int, BITBOARD);
        BITBOARD get_Rook_Attacks(int, BITBOARD);
        BITBOARD get_Queen_Attacks(int, BITBOARD);
        void init_leaper_attacks();
        void init_slider_attacks(int);
        void init_all();

        int countBits(BITBOARD);
        int indexLeastSigBit(BITBOARD);

        bool is_square_attacked(int, int);
        void print_attacked_squares(int);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ChessGame(sf::RenderTarget& target);
        ChessGame(){board = Board(800,800);};
        ~ChessGame(){};
};

#endif //CHESSGAME_H