#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <SFML/Graphics.hpp>

using namespace std;

class Board: public sf::Drawable{
    public:
        Board(int width, int height);
        
        const int coordinateMap[64] = {56,57,58,59,60,61,62,63,
                                       48,49,50,51,52,53,54,55,
                                       40,41,42,43,44,45,46,47,
                                       32,33,34,35,36,37,38,39,
                                       24,25,26,27,28,29,30,31,
                                       16,17,18,19,20,21,22,23,
                                        8, 9,10,11,12,13,14,15,
                                        0, 1, 2, 3, 4, 5, 6, 7};
        
        //BitBoards for different categories in regards of the board
        bitset<64> whiteSquares;
        bitset<64> blackSquares;
        bitset<64> emptySquares;
        bitset<64> occupiedSquares;
        bitset<64> whitePieces;
        bitset<64> blackPieces;

        //variable to hold the FEN string for the board positioning
        string FEN;

        bool b_player = true;       //true = white, false = black

        //BitBoards for piece types and colors
        bitset<64> whitePawn;
        bitset<64> whiteKnight;
        bitset<64> whiteBishop;
        bitset<64> whiteRook;
        bitset<64> whiteQueen;
        bitset<64> whiteKing;
        bitset<64> blackPawn;
        bitset<64> blackKnight;
        bitset<64> blackBishop;
        bitset<64> blackRook;
        bitset<64> blackQueen;
        bitset<64> blackKing;

        //vectors for piece boards by color
        vector<bitset<64> > whiteBoards;
        vector<bitset<64> > blackBoards;
        
        //Board representation squares
        sf::RectangleShape rectangles[64];

        //methods
        void loadBoard(int width, int height);
        void parseFen(string fen);
        ~Board(){};

        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //BOARD_H