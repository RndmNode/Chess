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

BITBOARD ChessGame::getBishopOccupancy(int square){
    BITBOARD attacks = 0ULL;

    int r, f;               // rank and file
    int tr = square / 8;    // target rank
    int tf = square % 8;    // target file

    for(r = tr+1, f = tf+1; r<=6 && f<=6; r++, f++) attacks |= (1ULL << ((r*8)+f));     // lower right
    for(r = tr-1, f = tf+1; r>=1 && f<=6; r--, f++) attacks |= (1ULL << ((r*8)+f));     // upper right
    for(r = tr+1, f = tf-1; r<=6 && f>=1; r++, f--) attacks |= (1ULL << ((r*8)+f));     // lower left
    for(r = tr-1, f = tf-1; r>=1 && f>=1; r--, f--) attacks |= (1ULL << ((r*8)+f));     // upper left

    return attacks;
}

BITBOARD ChessGame::getRookOccupancy(int square){
    BITBOARD attacks = 0ULL;

    int r, f;               // rank and file
    int tr = square / 8;    // target rank
    int tf = square % 8;    // target file

    for(r = tr+1; r<=6; r++) attacks |= (1ULL << ((r*8) + tf));   // down
    for(r = tr-1; r>=1; r--) attacks |= (1ULL << ((r*8) + tf));   // up
    for(f = tf+1; f<=6; f++) attacks |= (1ULL << ((tr*8) + f));   // right
    for(f = tf-1; f>=1; f--) attacks |= (1ULL << ((tr*8) + f));   // left

    return attacks;    
}

BITBOARD ChessGame::generateBishopAttacks(int square, BITBOARD blockers){
    BITBOARD attacks = 0ULL;

    int r, f;               // rank and file
    int tr = square / 8;    // target rank
    int tf = square % 8;    // target file

    for(r = tr+1, f = tf+1; r<=7 && f<=7; r++, f++){
        attacks |= (1ULL << ((r*8)+f));
        if((1ULL << ((r*8)+f) & blockers.to_ullong()) != 0ULL) break;
    }
    for(r = tr-1, f = tf+1; r>=0 && f<=7; r--, f++){
        attacks |= (1ULL << ((r*8)+f));
        if((1ULL << ((r*8)+f) & blockers.to_ullong()) != 0ULL) break;
    }
    for(r = tr+1, f = tf-1; r<=7 && f>=0; r++, f--){
        attacks |= (1ULL << ((r*8)+f));
        if((1ULL << ((r*8)+f) & blockers.to_ullong()) != 0ULL) break;
    }
    for(r = tr-1, f = tf-1; r>=0 && f>=0; r--, f--){
        attacks |= (1ULL << ((r*8)+f));
        if((1ULL << ((r*8)+f) & blockers.to_ullong()) != 0ULL) break;
    }

    return attacks;
}

BITBOARD ChessGame::generateRookAttacks(int square, BITBOARD blockers){
    BITBOARD attacks = 0ULL;

    int r, f;               // rank and file
    int tr = square / 8;    // target rank
    int tf = square % 8;    // target file

    for(r = tr+1; r<=7; r++){
        attacks |= (1ULL << ((r*8) + tf));
        if(((1ULL << ((r*8) + tf)) & blockers.to_ullong()) != 0ULL) break;
    }   
    for(r = tr-1; r>=0; r--){
        attacks |= (1ULL << ((r*8) + tf));
        if(((1ULL << ((r*8) + tf)) & blockers.to_ullong()) != 0ULL) break;
    } 
    for(f = tf+1; f<=7; f++){
        attacks |= (1ULL << ((tr*8) + f));
        if(((1ULL << ((tr*8) + f)) & blockers.to_ullong()) != 0ULL) break;
    } 
    for(f = tf-1; f>=0; f--){
        attacks |= (1ULL << ((tr*8) + f));
        if(((1ULL << ((tr*8) + f)) & blockers.to_ullong()) != 0ULL) break;
    } 

    return attacks;    
}

int ChessGame::countBits(BITBOARD bitboard){
    int count = 0;

    while(bitboard.to_ullong() > 0ULL){
        count++;
        bitboard &= bitboard.to_ullong() - 1;
    }

    return count;
}

int ChessGame::indexLeastSigBit(BITBOARD bitboard){
    if(bitboard.to_ullong() != 0ULL){
        return countBits((bitboard.to_ullong() & -bitboard.to_ullong()) - 1);
    }else return -1;
}

/*--------------DRAW--------------*/
void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(board);
}