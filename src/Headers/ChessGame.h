#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Board.h"
#include <string.h>
#include <sys/time.h>
#include <stack>

// encode moves into integers
#define encode_move(source, target, piece, promoted, capture, doublePush, enpassant, castling)\
    (source) |              \
    (target << 6) |         \
    (piece << 12) |         \
    (promoted << 16) |      \
    (capture << 20) |       \
    (doublePush << 21) |    \
    (enpassant << 22)  |    \
    (castling << 23)        

// extract move information
#define get_move_source(move)       (move & 0x3f)
#define get_move_target(move)       ((move & 0xfc0) >> 6)
#define get_move_piece(move)        ((move & 0xf000) >> 12)
#define get_move_promoted(move)     ((move & 0xf0000) >> 16)
#define get_move_capture(move)      (move & 0x100000)
#define get_move_doublePush(move)   (move & 0x200000)
#define get_move_enpassant(move)    (move & 0x400000)
#define get_move_castling(move)     (move & 0x800000)

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
extern const int castle_rights[64];

enum {all_moves, only_captures};

struct moves{
    int moves[256];     // moves
    int count;          // move count
};

class ChessGame: public sf::Drawable {
    public:
        // objects, vectors, enums
        Board board;
        moves m_list_of_moves[1];
        stack<string> move_history;

        // attributes
        // long nodes = 0;

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
        long generateMoves(moves *move_list);
        void add_move(moves* move_list, int move);
        void print_move(int move);
        void print_move_list(moves *move_list);
        int make_move(int move, int move_flag);
        void undo_move();

        // PERFT testing
        int time_in_ms();
        long PERFT_Driver(int depth);
        void PERFT_Test(int depth);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ChessGame(sf::RenderTarget& target);
        ChessGame(){board = Board(800,800);};
        ~ChessGame(){};
};

#endif //CHESSGAME_H