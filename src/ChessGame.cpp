#include "Headers/ChessGame.h"

// relevant occupancy bit count for every bishop position
const int bishop_relevant_bits[64] = {6, 5, 5, 5, 5, 5, 5, 6,
                                      5, 5, 5, 5, 5, 5, 5, 5,
                                      5, 5, 7, 7, 7, 7, 5, 5,
                                      5, 5, 7, 9, 9, 7, 5, 5,
                                      5, 5, 7, 9, 9, 7, 5, 5,
                                      5, 5, 7, 7, 7, 7, 5, 5,
                                      5, 5, 5, 5, 5, 5, 5, 5,
                                      6, 5, 5, 5, 5, 5, 5, 6};

// relevant occupancy bit count for every rook position
const int rook_relevant_bits[64] = {12, 11, 11, 11, 11, 11, 11, 12,
                                    11, 10, 10, 10, 10, 10, 10, 11,
                                    11, 10, 10, 10, 10, 10, 10, 11,
                                    11, 10, 10, 10, 10, 10, 10, 11,
                                    11, 10, 10, 10, 10, 10, 10, 11,
                                    11, 10, 10, 10, 10, 10, 10, 11,
                                    11, 10, 10, 10, 10, 10, 10, 11,
                                    12, 11, 11, 11, 11, 11, 11, 12};

ChessGame::ChessGame(sf::RenderTarget& target){
    board = Board(target.getSize().x,target.getSize().y);
}

// generate 32-bit pseudo random legal numbers
unsigned int ChessGame::get_random_U32_number(){
    // xor shift algorithm
    random_state ^= random_state << 13;
    random_state ^= random_state >> 17;
    random_state ^= random_state << 5;

    return random_state;
}

// generate 64-bit pseudo random legal numbers
BITBOARD ChessGame::get_random_U64_number(){
    // define 4 random numbers
    BITBOARD n1, n2, n3, n4;

    // init random numbers while isolating the "top" 16 bits
    n1 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);
    n2 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);
    n3 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);
    n4 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);

    // return random number
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

// generating magic number candidates
BITBOARD ChessGame::get_random_magic_number(){
    return get_random_U64_number() & get_random_U64_number() & get_random_U64_number();
}

// finds appropriate magic number 
BITBOARD ChessGame::find_magic_number(int square, int relevantBits, int bishopFlag){
    // init occupancies
    BITBOARD occupancies[4096];

    // init attack tables
    BITBOARD attacks[4096];
    
    // init used attacks
    BITBOARD used_attacks[4096];

    // init attack mask for current piece
    BITBOARD attack_mask = bishopFlag ? getBishopOccupancy(square) : getRookOccupancy(square);

    // init occupancy indicies
    int occupancy_indicies = 1 << relevantBits;

    // loop over occupancy indicies
    for(int index=0; index<occupancy_indicies; index++){
        // init occupancies 
        occupancies[index] = setOccupancies(index, relevantBits, attack_mask);
        // init attacks
        attacks[index] = bishopFlag ? generateBishopAttacks(square, occupancies[index]) : 
                                      generateRookAttacks(square, occupancies[index]);
    }

    // test magic numbers loop
    for(int random_count=0; random_count<100000000; random_count++){
        BITBOARD magic_number = get_random_magic_number();
        // skip inappropriate magic numbers
        if(countBits((attack_mask.to_ullong() * magic_number.to_ullong()) & 0xFF00000000000000) < 6) continue;

        // init used attacks
        memset(used_attacks, 0ULL, sizeof(used_attacks));

        // init index & fail flag
        int index, fail;
        
        // test magic index
        for(index=0, fail=0; !fail && index<occupancy_indicies; index++){
            // init magic index
            int magic_index = (int)(occupancies[index].to_ullong() * magic_number.to_ullong()) >> (64 - relevantBits);

            // if magic index works
            if(used_attacks[magic_index] == 0ULL){
                // init used attacks
                used_attacks[magic_index] = attacks[magic_index];
            }else if(used_attacks[magic_index] != attacks[magic_index]){
                fail = 1;
            }
        }

        // if magic number works, return it
        if(!fail) return magic_number;
    }
    // else
    cout << "Magic number failed!" << endl;
    return 0ULL;
}

// initialize magic numbers
void ChessGame::init_magic(){
    // loop over board squares
    for(int square=0; square<64; square++){
        // init rook magic numbers
        printf(" 0x%llxULL\n", find_magic_number(square, rook_relevant_bits[square], rook).to_ullong());
    }

    cout << "\n\n";
    for(int square=0; square<64; square++){
        // init bishop magic numbers
        printf(" 0x%llxULL\n", find_magic_number(square, bishop_relevant_bits[square], bishop).to_ullong());
    }
}

// Generates attacking bitboard for pawns depending on side and square
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

// Generates knight attacks depending on square
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

// Generates king attacks depending on square
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

// Initializes all attacking boards on all squares for pawns, knights, and kings
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

// Gets occupancy squares for bishops
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

// Gets occupancy squares for rooks
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

// Generates attacking bitboard for bishops while accounting for blocking pieces
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

// Generates attacking bitboard for rooks while accounting for blocking pieces
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

// Counts the number of set bits in a bitboard
int ChessGame::countBits(BITBOARD bitboard){
    int count = 0;

    while(bitboard.to_ullong() > 0ULL){
        count++;
        bitboard &= bitboard.to_ullong() - 1;
    }

    return count;
}

// Gets the index of the least significant bit in bitboard
int ChessGame::indexLeastSigBit(BITBOARD bitboard){
    if(bitboard.to_ullong() != 0ULL){
        return countBits((bitboard.to_ullong() & -bitboard.to_ullong()) - 1);
    }else return -1;
}

// Sets occupancy squares for piece depending on magic number
BITBOARD ChessGame::setOccupancies(int index, int bits_in_mask, BITBOARD attacks){
    BITBOARD occupancy = 0ULL;

    for(int count=0; count<bits_in_mask; count++){
        int square = indexLeastSigBit(attacks);
        attacks[square].flip();

        // check occupany with index to populate occupancy table
        if(index & (1 << count)){
            occupancy |= (1ULL << square);
        }
    }

    return occupancy;
}

/*--------------DRAW--------------*/
void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(board);
}