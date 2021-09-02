#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Piece.h"

using namespace std;

#define START_POSITION "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define BEHTING_STUDY "8/8/7p/3KNN1k/2p4p/8/3P2p1/8 w - - ; bm Kc6 "

//Globals
enum boardSquares {a8,b8,c8,d8,e8,f8,g8,h8,
                   a7,b7,c7,d7,e7,f7,g7,h7,
                   a6,b6,c6,d6,e6,f6,g6,h6,
                   a5,b5,c5,d5,e5,f5,g5,h5,
                   a4,b4,c4,d4,e4,f4,g4,h4,
                   a3,b3,c3,d3,e3,f3,g3,h3,
                   a2,b2,c2,d2,e2,f2,g2,h2,
                   a1,b1,c1,d1,e1,f1,g1,h1, no_sq};

enum sideToMove {white, black, both};
enum castling {wk = 1, wq = 2, bk = 4, bq = 8};
enum encoded_pieces {P, N, B, R, Q, K, p, n, b, r, q, k};
const map<char, int> char_to_piece {{'P',P}, {'N',N}, {'B',B}, {'R',R}, {'Q',Q}, {'K',K},
                                    {'p',p}, {'n',n}, {'b',b}, {'r',r}, {'q',q}, {'k',k}, {'/',-1}};
const map<char, int> piece_to_char {{P,'P'}, {N,'N'}, {B,'B'}, {R,'R'}, {Q,'Q'}, {K,'K'},
                                    {p,'p'}, {n,'n'}, {b,'b'}, {r,'r'}, {q,'q'}, {k,'k'}};


class Board: public sf::Drawable{
    public:
        Board(){};
        Board(int width, int height);

        string boardNames[12] = {"whitePawn","whiteKnight","whiteBishop","whiteRook","whiteQueen","whiteKing",
                                 "blackPawn","blackKnight","blackBishop","blackRook","blackQueen","blackKing"};

        //Methods
        void printBoard(int);
        void loadBoard(int width, int height);
        void findPieces();
        void placePiece(int, sf::Vector2f, int);
        int getBit(bitset<64>, int);
        void setBit(int board, boardSquares sqr){bitboards[board].set(sqr);};
        void setBit(int board, int sqr){bitboards[board].set(sqr);};

        vector<bitset<64> > bitboards;      // vector to hold piece bitboards ordered by encoded piece enumeration
        
        ~Board(){};

    private:
        //Objects, Vectors, enums
        vector<Piece> pieces;
        sf::RectangleShape rectangles[64];
        

        //Attributes
        char *FEN[];

        
        

        void parseFen(string);
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //BOARD_H