#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <map>
#include "Piece.h"

#define BITBOARD bitset<64>

using namespace std;

#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define DJAJA_STUDY "6R1/P2k4/r7/5N1P/r7/p7/7K/8 w - -"
#define HAKMEM_70 "5B2/6P1/1p6/8/1N6/kP6/2K5/8 w - - "
#define SZEN_POSITION "4k3/5ppp/8/8/8/8/PPP5/3K4 w - - "

//***---Global Board Constants---***//
enum boardSquares {a8,b8,c8,d8,e8,f8,g8,h8,
                   a7,b7,c7,d7,e7,f7,g7,h7,
                   a6,b6,c6,d6,e6,f6,g6,h6,
                   a5,b5,c5,d5,e5,f5,g5,h5,
                   a4,b4,c4,d4,e4,f4,g4,h4,
                   a3,b3,c3,d3,e3,f3,g3,h3,
                   a2,b2,c2,d2,e2,f2,g2,h2,
                   a1,b1,c1,d1,e1,f1,g1,h1, no_sq};

extern const char *square_to_coordinates[];

enum sideToMove {white, black, both};
enum {rook, bishop};        // flags for magic number generation
enum encoded_castling {wk = 1, wq = 2, bk = 4, bq = 8};
/*
    K       = 1
    KQ      = 3
    KQk     = 7
    KQkq    = 15
*/
enum encoded_pieces {P, N, B, R, Q, K, p, n, b, r, q, k};
const char charPieces[12] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};
const map<char, int> char_to_piece {{'P',P}, {'N',N}, {'B',B}, {'R',R}, {'Q',Q}, {'K',K},
                                    {'p',p}, {'n',n}, {'b',b}, {'r',r}, {'q',q}, {'k',k}, {'/',-1}};
const map<int, char> piece_to_char {{P,'P'}, {N,'N'}, {B,'B'}, {R,'R'}, {Q,'Q'}, {K,'K'},
                                    {p,'p'}, {n,'n'}, {b,'b'}, {r,'r'}, {q,'q'}, {k,'k'}};
const map<int, char> promoted_piece {{N,'n'}, {B,'b'}, {R,'r'}, {Q,'q'},
                                     {n,'n'}, {b,'b'}, {r,'R'}, {q,'Q'}};

// not_boards
extern const BITBOARD not_a_file;
extern const BITBOARD not_h_file;
extern const BITBOARD not_gh_file;
extern const BITBOARD not_ab_file;

//***----------------------------***//


class Board: public sf::Drawable{
    public:
        Board(){};
        Board(int width, int height);

        string boardNames[12] = {"whitePawn","whiteKnight","whiteBishop","whiteRook","whiteQueen","whiteKing",
                                 "blackPawn","blackKnight","blackBishop","blackRook","blackQueen","blackKing"};

        int side_to_move = -1;
        int enpassant_square = no_sq;
        int castling_rights;

        //Methods
        void printBoard(int);
        void printBitboard(BITBOARD);
        void loadBoard(int width, int height);
        void findPieces();
        void placePiece(int, sf::Vector2f, int);
        int getBit(BITBOARD, int);
        void setBit(int board, int sqr){bitboards[board].set(sqr);};
        static BITBOARD setBit(BITBOARD board, int sqr){board.set(sqr); return board;}

        vector<BITBOARD> bitboards;      // vector to hold piece bitboards ordered by encoded piece enumeration
        vector<BITBOARD> occupancies;
        vector<Piece> pieces;
        
        ~Board(){};

    private:
        //Objects, Vectors, enums
        sf::RectangleShape rectangles[64];

        //Attributes
        string FEN;

        void parseFen(string);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //BOARD_H