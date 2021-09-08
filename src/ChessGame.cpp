#include "Headers/ChessGame.h"

ChessGame::ChessGame(sf::RenderTarget& target){
    board = Board(target.getSize().x,target.getSize().y);
}

BITBOARD ChessGame::generatePawnAttacks(int side, int square){
    BITBOARD attacks = 0ULL;
    BITBOARD position = 0ULL;

    position = Board::setBit(position, square);

    if(!side){ // white
        if(((position >> 7) & not_a_file) != 0ULL) attacks |= (position >> 7);
        if(((position >> 9) & not_h_file) != 0ULL) attacks |= (position >> 9);
    }else{ // black
        if(((position << 7) & not_h_file) != 0ULL) attacks |= (position << 7);
        if(((position << 9) & not_a_file) != 0ULL) attacks |= (position << 9);
    }

    return attacks;
}

BITBOARD ChessGame::generateKnightAttacks(int square){
    BITBOARD attacks = 0ULL;
    BITBOARD position = 0ULL;

    position = Board::setBit(position, square);

    if(((position >> 15) & not_a_file) != 0ULL) attacks |= (position >> 15);
    if(((position >> 17) & not_h_file) != 0ULL) attacks |= (position >> 17);
    if(((position >> 6) & not_ab_file) != 0ULL) attacks |= (position >> 6);
    if(((position >> 10) & not_gh_file) != 0ULL) attacks |= (position >> 10);

    if(((position << 15) & not_h_file) != 0ULL) attacks |= (position << 15);
    if(((position << 17) & not_a_file) != 0ULL) attacks |= (position << 17);
    if(((position << 6) & not_gh_file) != 0ULL) attacks |= (position << 6);
    if(((position << 10) & not_ab_file) != 0ULL) attacks |= (position << 10);

    return attacks;
}

BITBOARD ChessGame::generateKingAttacks(int square){
    BITBOARD attacks = 0ULL;
    BITBOARD position = 0ULL;

    position = Board::setBit(position, square); // 1, 7, 8, 9

    if(((position >> 1) & not_h_file) != 0ULL) attacks |= (position >> 1);
    if(((position >> 7) & not_a_file) != 0ULL) attacks |= (position >> 7);
    if((position >> 8) != 0ULL) attacks |= (position >> 8);
    if(((position >> 9) & not_h_file) != 0ULL) attacks |= (position >> 9);

    if(((position << 1) & not_a_file) != 0ULL) attacks |= (position << 1);
    if(((position << 7) & not_h_file) != 0ULL) attacks |= (position << 7);
    if((position << 8) != 0ULL) attacks |= (position << 8);
    if(((position << 9) & not_a_file) != 0ULL) attacks |= (position << 9);

    return attacks;
}

void ChessGame::init_leaper_attacks(){
    for(int i=0; i<64; i++){
        // pawns
        pawn_attacks[white][i] = generatePawnAttacks(white, i);
        pawn_attacks[black][i] = generatePawnAttacks(black, i);

        // knights
        knight_attacks[i] = generateKnightAttacks(i);

        // kings
        king_attacks[i] = generateKingAttacks(i);
    }
}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(board);
}