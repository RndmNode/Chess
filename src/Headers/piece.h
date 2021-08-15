#ifndef PIECES_H
#define PIECES_H

#include <vector>

class piece{
    public:
        std::vector<int> moves;
        int coordinates[2];
};

#endif //PIECES_H