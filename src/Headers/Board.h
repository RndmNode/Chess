#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <SFML/Graphics.hpp>

using namespace std;

class Board{
    public:
        Board();
        int boardPieceMap[64] = {-1,-2,-3,-4,-5,-3,-2,-1,
                                 -6,-6,-6,-6,-6,-6,-6,-6,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  6, 6, 6, 6, 6, 6, 6, 6,
                                  1, 2, 3, 4, 5, 3, 2, 1};
        
        const int coordinateMap[64] = {56,57,58,59,60,61,62,63,
                                       48,49,50,51,52,53,54,55,
                                       40,41,42,43,44,45,46,47,
                                       32,33,34,35,36,37,38,39,
                                       24,25,26,27,28,29,30,31,
                                       16,17,18,19,20,21,22,23,
                                        8, 9,10,11,12,13,14,15,
                                        0, 1, 2, 3, 4, 5, 6, 7};
        
        const char *square_names[64] = {"a8","b8","c8","d8","e8","f8","g8","h8",
                                        "a7","b7","c7","d7","e7","f7","g7","h7",
                                        "a6","b6","c6","d6","e6","f6","g6","h6",
                                        "a5","b5","c5","d5","e5","f5","g5","h5",
                                        "a4","b4","c4","d4","e4","f4","g4","h4",
                                        "a3","b3","c3","d3","e3","f3","g3","h3",
                                        "a2","b2","c2","d2","e2","f2","g2","h2",
                                        "a1","b1","c1","d1","e1","f1","g1","h1"};
        
        bitset<64> whiteSquares;
        bitset<64> blackSquares;
        bitset<64> emptySquares;
        bitset<64> occupiedSquares;
        bitset<64> whitePieces;
        bitset<64> blackPieces;
        
        sf::Sprite sprites[64];
        void loadBoard(sf::RectangleShape rectangles[64], sf::Sprite sprites[16], int width, int height);
        void loadTextures(sf::Texture textures[64]);
        ~Board(){};
};

#endif //BOARD_H