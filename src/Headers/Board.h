#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <string>
#include <SFML/Graphics.hpp>
#include "Piece.h"

using namespace std;

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
// string boardNames[12] = {"whitePawn","whiteKnight","whiteBishop", ...}

class Board: public sf::Drawable{
    public:
        Board(int width, int height);
        ~Board(){};

    private:
        //Objects, Vectors, enums
        Piece pieces[32];
        sf::RectangleShape rectangles[64];
        vector<bitset<64> > bitboards;          // vector to hold piece bitboards ordered by encoded piece enumeration

        //Attributes
        string FEN;

        //Methods
        void printBoard(int);
        void loadBoard(int width, int height);
        //void parseFen(string fen);
        void setBit(int board, boardSquares sqr){bitboards[board].set(sqr);};
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //BOARD_H