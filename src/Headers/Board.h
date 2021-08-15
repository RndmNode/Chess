#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board{
    public:
        Board(){};
        int board[64] =         {-1,-2,-3,-4,-5,-3,-2,-1,
                                 -6,-6,-6,-6,-6,-6,-6,-6,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0,
                                  6, 6, 6, 6, 6, 6, 6, 6,
                                  1, 2, 3, 4, 5, 3, 2, 1};

        int coordinateMap[64] = { 1, 2, 3, 4, 5, 6, 7, 8,
                                  9,10,11,12,13,14,15,16,
                                 17,18,19,20,21,22,23,24,
                                 25,26,27,28,29,30,31,32,
                                 33,34,35,36,37,38,39,40,
                                 41,42,43,44,45,46,47,48,
                                 49,50,51,52,53,54,55,56,
                                 57,58,59,60,61,62,63,64};
        
        sf::Sprite sprites[64];
        void loadBoard(sf::RectangleShape rectangles[64], int width, int height);
        ~Board(){};
};

#endif //BOARD_H