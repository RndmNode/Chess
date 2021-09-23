#include "Headers/ChessGame.h"

BITBOARD pawn_attacks[2][64];
BITBOARD knight_attacks[64];
BITBOARD king_attacks[64];
BITBOARD bishop_masks[64];
BITBOARD rook_masks[64];
BITBOARD bishop_attacks[64][512];
BITBOARD rook_attacks[64][4096];
unsigned int random_state = 1804289383;

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

const int castle_rights[64] = {7, 15, 15, 15, 3, 15, 15, 11,
                              15, 15, 15, 15, 15, 15, 15, 15,
                              15, 15, 15, 15, 15, 15, 15, 15,
                              15, 15, 15, 15, 15, 15, 15, 15,
                              15, 15, 15, 15, 15, 15, 15, 15,
                              15, 15, 15, 15, 15, 15, 15, 15,
                              15, 15, 15, 15, 15, 15, 15, 15,
                              13, 15, 15, 15, 12, 15, 15, 14};

const BITBOARD rook_magic_numbers[64] = {
    0x8a80104000800020ULL, 0x140002000100040ULL, 0x2801880a0017001ULL, 0x100081001000420ULL,
    0x200020010080420ULL, 0x3001c0002010008ULL, 0x8480008002000100ULL, 0x2080088004402900ULL,
    0x800098204000ULL, 0x2024401000200040ULL, 0x100802000801000ULL, 0x120800800801000ULL,
    0x208808088000400ULL, 0x2802200800400ULL, 0x2200800100020080ULL, 0x801000060821100ULL,
    0x80044006422000ULL, 0x100808020004000ULL, 0x12108a0010204200ULL, 0x140848010000802ULL,
    0x481828014002800ULL, 0x8094004002004100ULL, 0x4010040010010802ULL, 0x20008806104ULL,
    0x100400080208000ULL, 0x2040002120081000ULL, 0x21200680100081ULL, 0x20100080080080ULL,
    0x2000a00200410ULL, 0x20080800400ULL, 0x80088400100102ULL, 0x80004600042881ULL,
    0x4040008040800020ULL, 0x440003000200801ULL, 0x4200011004500ULL, 0x188020010100100ULL,
    0x14800401802800ULL, 0x2080040080800200ULL, 0x124080204001001ULL, 0x200046502000484ULL,
    0x480400080088020ULL, 0x1000422010034000ULL, 0x30200100110040ULL, 0x100021010009ULL,
    0x2002080100110004ULL, 0x202008004008002ULL, 0x20020004010100ULL, 0x2048440040820001ULL,
    0x101002200408200ULL, 0x40802000401080ULL, 0x4008142004410100ULL, 0x2060820c0120200ULL,
    0x1001004080100ULL, 0x20c020080040080ULL, 0x2935610830022400ULL, 0x44440041009200ULL,
    0x280001040802101ULL, 0x2100190040002085ULL, 0x80c0084100102001ULL, 0x4024081001000421ULL,
    0x20030a0244872ULL, 0x12001008414402ULL, 0x2006104900a0804ULL, 0x1004081002402ULL
};

const BITBOARD bishop_magic_numbers[64] = {
    0x40040844404084ULL, 0x2004208a004208ULL, 0x10190041080202ULL, 0x108060845042010ULL,
    0x581104180800210ULL, 0x2112080446200010ULL, 0x1080820820060210ULL, 0x3c0808410220200ULL,
    0x4050404440404ULL, 0x21001420088ULL, 0x24d0080801082102ULL, 0x1020a0a020400ULL,
    0x40308200402ULL, 0x4011002100800ULL, 0x401484104104005ULL, 0x801010402020200ULL,
    0x400210c3880100ULL, 0x404022024108200ULL, 0x810018200204102ULL, 0x4002801a02003ULL,
    0x85040820080400ULL, 0x810102c808880400ULL, 0xe900410884800ULL, 0x8002020480840102ULL,
    0x220200865090201ULL, 0x2010100a02021202ULL, 0x152048408022401ULL, 0x20080002081110ULL,
    0x4001001021004000ULL, 0x800040400a011002ULL, 0xe4004081011002ULL, 0x1c004001012080ULL,
    0x8004200962a00220ULL, 0x8422100208500202ULL, 0x2000402200300c08ULL, 0x8646020080080080ULL,
    0x80020a0200100808ULL, 0x2010004880111000ULL, 0x623000a080011400ULL, 0x42008c0340209202ULL,
    0x209188240001000ULL, 0x400408a884001800ULL, 0x110400a6080400ULL, 0x1840060a44020800ULL,
    0x90080104000041ULL, 0x201011000808101ULL, 0x1a2208080504f080ULL, 0x8012020600211212ULL,
    0x500861011240000ULL, 0x180806108200800ULL, 0x4000020e01040044ULL, 0x300000261044000aULL,
    0x802241102020002ULL, 0x20906061210001ULL, 0x5a84841004010310ULL, 0x4010801011c04ULL,
    0xa010109502200ULL, 0x4a02012000ULL, 0x500201010098b028ULL, 0x8040002811040900ULL,
    0x28000010020204ULL, 0x6000020202d0240ULL, 0x8918844842082200ULL, 0x4010011029020020ULL
};

/*                          BINARY FORMATTING of MOVE ITEMS

    BINARY REPRESENTATION               DESCRIPTION             HEXIDECIMAL CONSTANTS
    =============================       =================       =====================
    0000 0000 0000 0000 0011 1111       source square           0x3f
    0000 0000 0000 1111 1100 0000       target square           0xfc0
    0000 0000 1111 0000 0000 0000       piece                   0xf000
    0000 1111 0000 0000 0000 0000       promoted piece          0xf0000
    0001 0000 0000 0000 0000 0000       capture flag            0x100000
    0010 0000 0000 0000 0000 0000       double push flag        0x200000
    0100 0000 0000 0000 0000 0000       enpassant capture       0x400000
    1000 0000 0000 0000 0000 0000       castling flag           0x800000

*/

ChessGame::ChessGame(sf::RenderTarget& target){
    board = Board(target.getSize().x,target.getSize().y);
}

// // generate 32-bit pseudo random legal numbers
// unsigned int ChessGame::get_random_U32_number(){
//     // xor shift algorithm
//     random_state ^= random_state << 13;
//     random_state ^= random_state >> 17;
//     random_state ^= random_state << 5;

//     return random_state;
// }

// // generate 64-bit pseudo random legal numbers
// BITBOARD ChessGame::get_random_U64_number(){
//     // define 4 random numbers
//     BITBOARD n1, n2, n3, n4;

//     // init random numbers while isolating the "top" 16 bits
//     n1 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);
//     n2 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);
//     n3 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);
//     n4 = (BITBOARD)(get_random_U32_number()) & (BITBOARD)(0xFFFF);

//     // return random number
//     return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
// }

// // generating magic number candidates
// BITBOARD ChessGame::get_random_magic_number(){
//     return get_random_U64_number() & get_random_U64_number() & get_random_U64_number();
// }

// // finds appropriate magic number 
// BITBOARD ChessGame::find_magic_number(int square, int relevantBits, int bishopFlag){
//     // init occupancies
//     BITBOARD occupancies[4096];

//     // init attack tables
//     BITBOARD attacks[4096];
    
//     // init used attacks
//     BITBOARD used_attacks[4096];

//     // init attack mask for current piece
//     BITBOARD attack_mask = bishopFlag ? getBishopOccupancy(square) : getRookOccupancy(square);

//     // init occupancy indicies
//     int occupancy_indicies = 1 << relevantBits;

//     // loop over occupancy indicies
//     for(int index=0; index<occupancy_indicies; index++){
//         // init occupancies 
//         occupancies[index] = setOccupancies(index, relevantBits, attack_mask);
//         // init attacks
//         attacks[index] = bishopFlag ? generateBishopAttacks_onTheFly(square, occupancies[index]) : 
//                                       generateRookAttacks_onTheFly(square, occupancies[index]);
//     }

//     // test magic numbers loop
//     for(int random_count=0; random_count<10000000; random_count++){
//         // generate magic number candidate
//         BITBOARD magic_number = get_random_magic_number(); 
//         // skip inappropriate magic numbers
//         if(countBits((attack_mask.to_ullong() * magic_number.to_ullong()) & 0xFF00000000000000) < 6) continue;

//         // init used attacks
//         memset(used_attacks, 0ULL, sizeof(used_attacks));

//         // init index & fail flag
//         int index, fail;
        
//         // test magic index
//         for(index=0, fail=0; !fail && index<occupancy_indicies; index++){
//             // init magic index
//             int magic_index = (int)((occupancies[index].to_ullong() * magic_number.to_ullong()) >> (64 - relevantBits));

//             // if magic index works
//             if(used_attacks[magic_index] == 0ULL){
//                 // init used attacks
//                 used_attacks[magic_index] = attacks[index];
//             }else if(used_attacks[magic_index] != attacks[index]){
//                 fail = 1;
//             }
//         }

//         // if magic number works, return it
//         if(!fail) return magic_number;
//     }
//     // else
//     cout << "Magic number failed!" << endl;
//     return 0ULL;
// }

// // initialize magic numbers
// void ChessGame::init_magic(){
//     // loop over board squares
//     for(int square=0; square<64; square++){
//         // init rook magic numbers
//         rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], rook);
//     }

//     cout << "\n\n";
//     for(int square=0; square<64; square++){
//         // init bishop magic numbers
//         bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], bishop);
//     }
// }

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

// Initializes all attacking boards on all squares for rooks, bishops, and queens
void ChessGame::init_slider_attacks(int bishopFlag){
    // loop over 64 board squares
    for(int square=0; square<64; square++){
        // init masks
        bishop_masks[square] = getBishopOccupancy(square);
        rook_masks[square] = getRookOccupancy(square);

        // init current mask
        BITBOARD attack_mask = bishopFlag ? bishop_masks[square] : rook_masks[square];

        // init relevant bit count
        int relevant_bit_count = countBits(attack_mask);

        // init occupancy indicies
        int occupancy_indicies = 1 << relevant_bit_count;

        // loop over occupany indicies
        for(int index=0; index<occupancy_indicies; index++){
            // bishop
            if(bishopFlag){
                // init current occupancy variation
                BITBOARD occupancy = setOccupancies(index, relevant_bit_count, attack_mask);

                //init magic index
                int magic_index = (occupancy.to_ullong() * bishop_magic_numbers[square].to_ullong()) >> (64-bishop_relevant_bits[square]);

                // init bishop attacks
                bishop_attacks[square][magic_index] = generateBishopAttacks_onTheFly(square, occupancy);
            }else{  // rook
                // init current occupancy variation
                BITBOARD occupancy = setOccupancies(index, relevant_bit_count, attack_mask);

                //init magic index
                int magic_index = (occupancy.to_ullong() * rook_magic_numbers[square].to_ullong()) >> (64-rook_relevant_bits[square]);

                // init rook attacks
                rook_attacks[square][magic_index] = generateRookAttacks_onTheFly(square, occupancy);
            }
        }
    }
}

// get bishop attacks
BITBOARD ChessGame::get_Bishop_Attacks(int square, BITBOARD occupancy){
    // get bishop attacks assuming current board occupancy
    occupancy &= bishop_masks[square];
    occupancy = occupancy.to_ullong() * bishop_magic_numbers[square].to_ullong();
    occupancy >>= 64 - bishop_relevant_bits[square];

    return bishop_attacks[square][occupancy.to_ullong()];
}

// get rook attacks
BITBOARD ChessGame::get_Rook_Attacks(int square, BITBOARD occupancy){
    // get rook attacks assuming current board occupancy
    occupancy &= rook_masks[square];
    occupancy = occupancy.to_ullong() * rook_magic_numbers[square].to_ullong();
    occupancy >>= 64 - rook_relevant_bits[square];

    return rook_attacks[square][occupancy.to_ullong()];
}


// Gets occupancy squares for bishops (in video series, this is equal to mask_bishop_attacks)
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

// Gets occupancy squares for rooks (in video series, this is equal to mask_rook_attacks)
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

// Generates attacking bitboard for bishops while accounting for blocking pieces (in video series, this is equal to bishop_attacks_on_the_fly)
BITBOARD ChessGame::generateBishopAttacks_onTheFly(int square, BITBOARD blockers){
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

// Generates attacking bitboard for rooks while accounting for blocking pieces (in video series, this is equal to rook_attacks_on_the_fly)
BITBOARD ChessGame::generateRookAttacks_onTheFly(int square, BITBOARD blockers){
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

BITBOARD ChessGame::get_Queen_Attacks(int square, BITBOARD occupancy){
    // init holder boards
    BITBOARD queen_attacks = 0ULL;
    BITBOARD bishopOccupancies = occupancy;
    BITBOARD rookOccupancies = occupancy;

    // get rook attacks assuming current board occupancy
    bishopOccupancies &= bishop_masks[square];
    bishopOccupancies = bishopOccupancies.to_ullong() * bishop_magic_numbers[square].to_ullong();
    bishopOccupancies >>= 64 - bishop_relevant_bits[square];

    // get bishop attacks
    queen_attacks = bishop_attacks[square][bishopOccupancies.to_ullong()];

    // get rook attacks assuming current board occupancy
    rookOccupancies &= rook_masks[square];
    rookOccupancies = rookOccupancies.to_ullong() * rook_magic_numbers[square].to_ullong();
    rookOccupancies >>= 64 - rook_relevant_bits[square];
    
    // get rook attacks
    queen_attacks |= rook_attacks[square][rookOccupancies.to_ullong()];

    return queen_attacks;
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

// Sets occupancy squares for pieces given magic number index
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

void ChessGame::init_all(){
    init_leaper_attacks();
    init_slider_attacks(bishop);
    init_slider_attacks(rook);
    generateMoves(m_list_of_moves);
}

/**********************************\
 ==================================
          Move Generation
 ==================================
\**********************************/

bool ChessGame::is_square_attacked(int square, int side){
    // attacked by white pawns
    if((side == white) && (pawn_attacks[black][square] & board.bitboards[P]).to_ullong()) return true;

    // attacked by black pawns
    if((side == black) && (pawn_attacks[white][square] & board.bitboards[p]).to_ullong()) return true;

    // attacked by knights
    if(knight_attacks[square].to_ullong() & ((side == white) ? board.bitboards[N]: board.bitboards[n]).to_ullong()) return true;

    // attacked by kings
    if(king_attacks[square].to_ullong() & ((side == white) ? board.bitboards[K]: board.bitboards[k]).to_ullong()) return true;

    // attacked by bishops
    if(get_Bishop_Attacks(square, board.occupancies[both]).to_ullong() & ((side == white) ? board.bitboards[B] : board.bitboards[b]).to_ullong()) return true;

    // attacked by rooks
    if(get_Rook_Attacks(square, board.occupancies[both]).to_ullong() & ((side == white) ? board.bitboards[R] : board.bitboards[r]).to_ullong()) return true;

    // attacked by queens
    if(get_Queen_Attacks(square, board.occupancies[both]).to_ullong() & ((side == white) ? board.bitboards[Q] : board.bitboards[q]).to_ullong()) return true;

    // by default, return false
    return false;
}

// printing all squares attacked given a side
void ChessGame::print_attacked_squares(int side){
    cout << "\n";
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            int square = (rank*8)+file;
            if(!file) cout << "  " << 8-rank << " ";
            int answer = is_square_attacked(square, side) ? 1 : 0;
            cout << " " << answer;
        }
        cout << "\n";
    }
    cout << "\n     a b c d e f g h\n\n";
}

// // generate all moves
// void ChessGame::generateMoves(){

//     // cout << "generating moves...\n";
//     // init move count
//     m_list_of_moves->count = 0;

//     // define source and target squares
//     int sourceSquare, targetSquare;

//     // define current piece's bitboard copy & its attacks
//     BITBOARD bitboard, attacks;

//     // loop over all bitboards
//     for(int piece=P; piece<=k; piece++){
//         // init bitboard copy
//         bitboard = board.bitboards[piece];

//         // generate white pawns & white king castling
//         if(board.side_to_move == white){
//             // Pawns
//             if(piece == P){
//                 // while pieces have not been accounted for (bitboard.to_ullong() is greater than 0)
//                 while(bitboard.to_ullong()){
//                     // init source and target square
//                     sourceSquare = indexLeastSigBit(bitboard);
//                     targetSquare = sourceSquare - 8;

//                     // generate quiet pawn moves
//                     if(!(targetSquare < a8) && !board.getBit(board.occupancies[both],targetSquare)){
//                         // if pawn promotion
//                         if(sourceSquare >= a7 && sourceSquare <= h7){
//                             //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
//                             add_move(encode_move(sourceSquare, targetSquare, piece, Q, 0, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, R, 0, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, B, 0, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, N, 0, 0, 0, 0));
//                         }else{
//                             // one square ahead
//                             //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
//                             add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                            
//                             // two squares ahead
//                             if((sourceSquare >= a2 && sourceSquare <= h2) && !board.getBit(board.occupancies[both], targetSquare - 8)){
//                                 //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
//                                 add_move(encode_move(sourceSquare, (targetSquare-8), piece, 0, 0, 1, 0, 0));
//                             }
//                         }
//                     }

//                     // init pawn attacks bitboard
//                     attacks = pawn_attacks[board.side_to_move][sourceSquare] & board.occupancies[black];

//                     // generate pawn captures
//                     while(attacks.to_ullong()){
//                         targetSquare = indexLeastSigBit(attacks);

//                         // handle capture and promotion combo
//                         if(sourceSquare >= a7 && sourceSquare <= h7){
//                             //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
//                             add_move(encode_move(sourceSquare, targetSquare, piece, Q, 1, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, R, 1, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, B, 1, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, N, 1, 0, 0, 0));
//                         }else{
//                             //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
//                             add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                         }
//                         // pop LS1B from bitboard copy
//                         attacks.flip(targetSquare);
//                     }

//                     // generate enpassant captures
//                     if(board.enpassant_square != no_sq){
//                         BITBOARD enpassant_attacks = pawn_attacks[board.side_to_move][sourceSquare].to_ullong() & (1ULL << board.enpassant_square);

//                         // if enpassant is available
//                         if(enpassant_attacks.to_ullong()){
//                             int enpassant_target = indexLeastSigBit(enpassant_attacks);
//                             add_move(encode_move(sourceSquare, enpassant_target, piece, 0, 1, 0, 1, 0));
//                         }
//                     }

//                     // pop LS1B from bitboard copy
//                     bitboard.flip(sourceSquare);
//                 }
//             }

//             // castling moves
//             if(piece == K){
//                 // king side castling
//                 if(board.castling_rights & wk){
//                     // make sure no pieces are between the king and king's rook
//                     if (!board.getBit(board.occupancies[both], f1) && !board.getBit(board.occupancies[both], g1)){
//                         // make sure king is not moving out of, or through, check
//                         if(!is_square_attacked(e1, black) && !is_square_attacked(f1, black)){
//                             add_move(encode_move(e1, g1, piece, 0, 0, 0, 0, 1));
//                         }
//                     }
//                 }

//                 // queen side castling
//                 if(board.castling_rights & wq){
//                     // make sure no pieces are between the king and queen's rook
//                     if (!board.getBit(board.occupancies[both], d1) && !board.getBit(board.occupancies[both], c1) && !board.getBit(board.occupancies[both], b1)){
//                         // make sure king is not moving out of, or through, check
//                         if(!is_square_attacked(e1, black) && !is_square_attacked(d1, black)){
//                             add_move(encode_move(e1, c1, piece, 0, 0, 0, 0, 1));
//                         }
//                     }
//                 }
//             }
//         } else {    // black pawns & king castling
//             // Pawns
//             if(piece == p){
//                 // while pieces have not been accounted for (bitboard.to_ullong() is greater than 0)
//                 while(bitboard.to_ullong()){
//                     // init source and target square
//                     sourceSquare = indexLeastSigBit(bitboard);
//                     targetSquare = sourceSquare + 8;

//                     // generate quiet pawn moves
//                     if(!(targetSquare < a8) && !board.getBit(board.occupancies[both],targetSquare)){
//                         // if pawn promotion
//                         if(sourceSquare >= a2 && sourceSquare <= h2){
//                             //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
//                             add_move(encode_move(sourceSquare, targetSquare, piece, q, 0, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, r, 0, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, b, 0, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, n, 0, 0, 0, 0));
//                         }else{
//                             // one square ahead
//                             //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
//                             add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));

//                             // two squares ahead
//                             if((sourceSquare >= a7 && sourceSquare <= h7) && !board.getBit(board.occupancies[both], targetSquare + 8)){
//                                 //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
//                                 add_move(encode_move(sourceSquare, (targetSquare+8), piece, 0, 0, 1, 0, 0));
//                             }
//                         }
//                     }

//                     // init pawn attacks bitboard
//                     attacks = pawn_attacks[board.side_to_move][sourceSquare] & board.occupancies[white];

//                     // generate pawn captures
//                     while(attacks.to_ullong()){
//                         targetSquare = indexLeastSigBit(attacks);

//                         // handle capture and promotion combo
//                         if(sourceSquare >= a2 && sourceSquare <= h2){
//                             //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
//                             add_move(encode_move(sourceSquare, targetSquare, piece, q, 1, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, r, 1, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, b, 1, 0, 0, 0));
//                             add_move(encode_move(sourceSquare, targetSquare, piece, n, 1, 0, 0, 0));
//                         }else{  // captures
//                             //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
//                             add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                         }
//                         // pop LS1B from bitboard copy
//                         attacks.flip(targetSquare);
//                     }

//                     // generate enpassant captures
//                     if(board.enpassant_square != no_sq){
//                         BITBOARD enpassant_attacks = pawn_attacks[board.side_to_move][sourceSquare].to_ullong() & (1ULL << board.enpassant_square);

//                         // if enpassant is available
//                         if(enpassant_attacks.to_ullong()){
//                             int enpassant_target = indexLeastSigBit(enpassant_attacks);
//                             add_move(encode_move(sourceSquare, enpassant_target, piece, 0, 1, 0, 1, 0));
//                         }
//                     }
//                     // pop LS1B from bitboard copy
//                     bitboard.flip(sourceSquare);
//                 }
//             }

//             // castling moves
//             if(piece == k){
//                 // king side castling
//                 if(board.castling_rights & bk){
//                     // make sure no pieces are between the king and king's rook
//                     if (!board.getBit(board.occupancies[both], f8) && !board.getBit(board.occupancies[both], g8)){
//                         // make sure king is not moving out of, or through, check
//                         if(!is_square_attacked(e8, white) && !is_square_attacked(f8, white)){
//                             add_move(encode_move(e8, g8, piece, 0, 0, 0, 0, 1));
//                         }
//                     }
//                 }

//                 // queen side castling
//                 if(board.castling_rights & bq){
//                     // make sure no pieces are between the king and queen's rook
//                     if (!board.getBit(board.occupancies[both], d8) && !board.getBit(board.occupancies[both], c8) && !board.getBit(board.occupancies[both], b8)){
//                         // make sure king is not moving out of, or through, check
//                         if(!is_square_attacked(e8, white) && !is_square_attacked(d8, white)){
//                             add_move(encode_move(e8, c8, piece, 0, 0, 0, 0, 1));
//                         }
//                     }
//                 }
//             }
//         }

//         // generate knight moves
//         if((board.side_to_move == white) ? piece == N : piece == n){
//             // loop over source squares of piece bitboard copy
//             while(bitboard.to_ullong()){
//                 // init source square
//                 sourceSquare = indexLeastSigBit(bitboard);

//                 // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
//                 attacks = knight_attacks[sourceSquare] & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

//                 while (attacks.to_ullong()){
//                     // init target square
//                     targetSquare = indexLeastSigBit(attacks);

//                     // quiet move
//                     if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
//                     } else { // captures
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                     }

//                     // pop ls1b
//                     attacks.flip(targetSquare);
//                 }
//                 // pop ls1b
//                 bitboard.flip(sourceSquare);
//             }
//         }
        
//         // generate bishop moves
//         if((board.side_to_move == white) ? piece == B : piece == b){
//             // loop over source squares of piece bitboard copy
//             while(bitboard.to_ullong()){
//                 // init source square
//                 sourceSquare = indexLeastSigBit(bitboard);

//                 // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
//                 attacks = get_Bishop_Attacks(sourceSquare,board.occupancies[both]) & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

//                 // loop over attack squares of attack bitboard
//                 while (attacks.to_ullong()){
//                     // init target square
//                     targetSquare = indexLeastSigBit(attacks);

//                     // quiet move
//                     if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
//                     } else { // captures
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                     }

//                     // pop ls1b
//                     attacks.flip(targetSquare);
//                 }
//                 // pop ls1b
//                 bitboard.flip(sourceSquare);
//             }
//         }

//         // generate rook moves
//         if((board.side_to_move == white) ? piece == R : piece == r){
//             // loop over source squares of piece bitboard copy
//             while(bitboard.to_ullong()){
//                 // init source square
//                 sourceSquare = indexLeastSigBit(bitboard);

//                 // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
//                 attacks = get_Rook_Attacks(sourceSquare,board.occupancies[both]) & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

//                 // loop over attack squares of attack bitboard
//                 while (attacks.to_ullong()){
//                     // init target square
//                     targetSquare = indexLeastSigBit(attacks);

//                     // quiet move
//                     if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
//                     } else { // captures
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                     }

//                     // pop ls1b
//                     attacks.flip(targetSquare);
//                 }
//                 // pop ls1b
//                 bitboard.flip(sourceSquare);
//             }
//         }

//         // generate queen moves
//         if((board.side_to_move == white) ? piece == Q : piece == q){
//             // loop over source squares of piece bitboard copy
//             while(bitboard.to_ullong()){
//                 // init source square
//                 sourceSquare = indexLeastSigBit(bitboard);

//                 // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
//                 attacks = get_Queen_Attacks(sourceSquare,board.occupancies[both]) & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

//                 // loop over attack squares of attack bitboard
//                 while (attacks.to_ullong()){
//                     // init target square
//                     targetSquare = indexLeastSigBit(attacks);

//                     // quiet move
//                     if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
//                     } else { // captures
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                     }

//                     // pop ls1b
//                     attacks.flip(targetSquare);
//                 }
//                 // pop ls1b
//                 bitboard.flip(sourceSquare);
//             }
//         }

//         // generate king moves
//         if((board.side_to_move == white) ? piece == K : piece == k){
//             // loop over source squares of piece bitboard copy
//             while(bitboard.to_ullong()){
//                 // init source square
//                 sourceSquare = indexLeastSigBit(bitboard);

//                 // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
//                 attacks = king_attacks[sourceSquare] & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

//                 // loop over attack squares of attack bitboard
//                 while (attacks.to_ullong()){
//                     // init target square
//                     targetSquare = indexLeastSigBit(attacks);

//                     // quiet move
//                     if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
//                     } else { // captures
//                         add_move(encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
//                     }

//                     // pop ls1b
//                     attacks.flip(targetSquare);
//                 }
//                 // pop ls1b
//                 bitboard.flip(sourceSquare);
//             }
//         }
//     }
//     // cout << "Total moves generated: " << m_list_of_moves->count << "\n";
// }

// generate all moves
long ChessGame::generateMoves(moves *move_list){

    // cout << "generating moves...\n";
    // init move count
    move_list->count = 0;

    // define source and target squares
    int sourceSquare, targetSquare;

    // define current piece's bitboard copy & its attacks
    BITBOARD bitboard, attacks;

    // loop over all bitboards
    for(int piece=P; piece<=k; piece++){
        // init bitboard copy
        bitboard = board.bitboards[piece];

        // generate white pawns & white king castling
        if(board.side_to_move == white){
            // Pawns
            if(piece == P){
                // while pieces have not been accounted for (bitboard.to_ullong() is greater than 0)
                while(bitboard.to_ullong()){
                    // init source and target square
                    sourceSquare = indexLeastSigBit(bitboard);
                    targetSquare = sourceSquare - 8;

                    // generate quiet pawn moves
                    if(!(targetSquare < a8) && !board.getBit(board.occupancies[both],targetSquare)){
                        // if pawn promotion
                        if(sourceSquare >= a7 && sourceSquare <= h7){
                            //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, Q, 0, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, R, 0, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, B, 0, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, N, 0, 0, 0, 0));
                        }else{
                            // one square ahead
                            //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                            
                            // two squares ahead
                            if((sourceSquare >= a2 && sourceSquare <= h2) && !board.getBit(board.occupancies[both], targetSquare - 8)){
                                //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
                                add_move(move_list, encode_move(sourceSquare, (targetSquare-8), piece, 0, 0, 1, 0, 0));
                            }
                        }
                    }

                    // init pawn attacks bitboard
                    attacks = pawn_attacks[board.side_to_move][sourceSquare] & board.occupancies[black];

                    // generate pawn captures
                    while(attacks.to_ullong()){
                        targetSquare = indexLeastSigBit(attacks);

                        // handle capture and promotion combo
                        if(sourceSquare >= a7 && sourceSquare <= h7){
                            //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, Q, 1, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, R, 1, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, B, 1, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, N, 1, 0, 0, 0));
                        }else{
                            //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                        }
                        // pop LS1B from bitboard copy
                        attacks.flip(targetSquare);
                    }

                    // generate enpassant captures
                    if(board.enpassant_square != no_sq){
                        BITBOARD enpassant_attacks = pawn_attacks[board.side_to_move][sourceSquare].to_ullong() & (1ULL << board.enpassant_square);

                        // if enpassant is available
                        if(enpassant_attacks.to_ullong()){
                            int enpassant_target = indexLeastSigBit(enpassant_attacks);
                            add_move(move_list, encode_move(sourceSquare, enpassant_target, piece, 0, 1, 0, 1, 0));
                        }
                    }

                    // pop LS1B from bitboard copy
                    bitboard.flip(sourceSquare);
                }
            }

            // castling moves
            if(piece == K){
                // king side castling
                if(board.castling_rights & wk){
                    // make sure no pieces are between the king and king's rook
                    if (!board.getBit(board.occupancies[both], f1) && !board.getBit(board.occupancies[both], g1)){
                        // make sure king is not moving out of, or through, check
                        if(!is_square_attacked(e1, black) && !is_square_attacked(f1, black)){
                            add_move(move_list, encode_move(e1, g1, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }

                // queen side castling
                if(board.castling_rights & wq){
                    // make sure no pieces are between the king and queen's rook
                    if (!board.getBit(board.occupancies[both], d1) && !board.getBit(board.occupancies[both], c1) && !board.getBit(board.occupancies[both], b1)){
                        // make sure king is not moving out of, or through, check
                        if(!is_square_attacked(e1, black) && !is_square_attacked(d1, black)){
                            add_move(move_list, encode_move(e1, c1, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }
            }
        } else {    // black pawns & king castling
            // Pawns
            if(piece == p){
                // while pieces have not been accounted for (bitboard.to_ullong() is greater than 0)
                while(bitboard.to_ullong()){
                    // init source and target square
                    sourceSquare = indexLeastSigBit(bitboard);
                    targetSquare = sourceSquare + 8;

                    // generate quiet pawn moves
                    if(!(targetSquare < a8) && !board.getBit(board.occupancies[both],targetSquare)){
                        // if pawn promotion
                        if(sourceSquare >= a2 && sourceSquare <= h2){
                            //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, q, 0, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, r, 0, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, b, 0, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, n, 0, 0, 0, 0));
                        }else{
                            // one square ahead
                            //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));

                            // two squares ahead
                            if((sourceSquare >= a7 && sourceSquare <= h7) && !board.getBit(board.occupancies[both], targetSquare + 8)){
                                //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
                                add_move(move_list, encode_move(sourceSquare, (targetSquare+8), piece, 0, 0, 1, 0, 0));
                            }
                        }
                    }

                    // init pawn attacks bitboard
                    attacks = pawn_attacks[board.side_to_move][sourceSquare] & board.occupancies[white];

                    // generate pawn captures
                    while(attacks.to_ullong()){
                        targetSquare = indexLeastSigBit(attacks);

                        // handle capture and promotion combo
                        if(sourceSquare >= a2 && sourceSquare <= h2){
                            //------ ADD FOUR MOVES TO MOVE LIST (PROMOTE TO Q, R, N, B)
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, q, 1, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, r, 1, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, b, 1, 0, 0, 0));
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, n, 1, 0, 0, 0));
                        }else{  // captures
                            //------ ADD ONE MOVE FROM SOURCE TO TARGET SQUARE
                            add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                        }
                        // pop LS1B from bitboard copy
                        attacks.flip(targetSquare);
                    }

                    // generate enpassant captures
                    if(board.enpassant_square != no_sq){
                        BITBOARD enpassant_attacks = pawn_attacks[board.side_to_move][sourceSquare].to_ullong() & (1ULL << board.enpassant_square);

                        // if enpassant is available
                        if(enpassant_attacks.to_ullong()){
                            int enpassant_target = indexLeastSigBit(enpassant_attacks);
                            add_move(move_list, encode_move(sourceSquare, enpassant_target, piece, 0, 1, 0, 1, 0));
                        }
                    }
                    // pop LS1B from bitboard copy
                    bitboard.flip(sourceSquare);
                }
            }

            // castling moves
            if(piece == k){
                // king side castling
                if(board.castling_rights & bk){
                    // make sure no pieces are between the king and king's rook
                    if (!board.getBit(board.occupancies[both], f8) && !board.getBit(board.occupancies[both], g8)){
                        // make sure king is not moving out of, or through, check
                        if(!is_square_attacked(e8, white) && !is_square_attacked(f8, white)){
                            add_move(move_list, encode_move(e8, g8, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }

                // queen side castling
                if(board.castling_rights & bq){
                    // make sure no pieces are between the king and queen's rook
                    if (!board.getBit(board.occupancies[both], d8) && !board.getBit(board.occupancies[both], c8) && !board.getBit(board.occupancies[both], b8)){
                        // make sure king is not moving out of, or through, check
                        if(!is_square_attacked(e8, white) && !is_square_attacked(d8, white)){
                            add_move(move_list, encode_move(e8, c8, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }
            }
        }

        // generate knight moves
        if((board.side_to_move == white) ? piece == N : piece == n){
            // loop over source squares of piece bitboard copy
            while(bitboard.to_ullong()){
                // init source square
                sourceSquare = indexLeastSigBit(bitboard);

                // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
                attacks = knight_attacks[sourceSquare] & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

                while (attacks.to_ullong()){
                    // init target square
                    targetSquare = indexLeastSigBit(attacks);

                    // quiet move
                    if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                    } else { // captures
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                    }

                    // pop ls1b
                    attacks.flip(targetSquare);
                }
                // pop ls1b
                bitboard.flip(sourceSquare);
            }
        }
        
        // generate bishop moves
        if((board.side_to_move == white) ? piece == B : piece == b){
            // loop over source squares of piece bitboard copy
            while(bitboard.to_ullong()){
                // init source square
                sourceSquare = indexLeastSigBit(bitboard);

                // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
                attacks = get_Bishop_Attacks(sourceSquare,board.occupancies[both]) & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

                // loop over attack squares of attack bitboard
                while (attacks.to_ullong()){
                    // init target square
                    targetSquare = indexLeastSigBit(attacks);

                    // quiet move
                    if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                    } else { // captures
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                    }

                    // pop ls1b
                    attacks.flip(targetSquare);
                }
                // pop ls1b
                bitboard.flip(sourceSquare);
            }
        }

        // generate rook moves
        if((board.side_to_move == white) ? piece == R : piece == r){
            // loop over source squares of piece bitboard copy
            while(bitboard.to_ullong()){
                // init source square
                sourceSquare = indexLeastSigBit(bitboard);

                // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
                attacks = get_Rook_Attacks(sourceSquare,board.occupancies[both]) & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

                // loop over attack squares of attack bitboard
                while (attacks.to_ullong()){
                    // init target square
                    targetSquare = indexLeastSigBit(attacks);

                    // quiet move
                    if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                    } else { // captures
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                    }

                    // pop ls1b
                    attacks.flip(targetSquare);
                }
                // pop ls1b
                bitboard.flip(sourceSquare);
            }
        }

        // generate queen moves
        if((board.side_to_move == white) ? piece == Q : piece == q){
            // loop over source squares of piece bitboard copy
            while(bitboard.to_ullong()){
                // init source square
                sourceSquare = indexLeastSigBit(bitboard);

                // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
                attacks = get_Queen_Attacks(sourceSquare,board.occupancies[both]) & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

                // loop over attack squares of attack bitboard
                while (attacks.to_ullong()){
                    // init target square
                    targetSquare = indexLeastSigBit(attacks);

                    // quiet move
                    if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                    } else { // captures
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                    }

                    // pop ls1b
                    attacks.flip(targetSquare);
                }
                // pop ls1b
                bitboard.flip(sourceSquare);
            }
        }

        // generate king moves
        if((board.side_to_move == white) ? piece == K : piece == k){
            // loop over source squares of piece bitboard copy
            while(bitboard.to_ullong()){
                // init source square
                sourceSquare = indexLeastSigBit(bitboard);

                // init piece attacks in order to get set of target squares (avoids attacking own pieces given side-to-move)
                attacks = king_attacks[sourceSquare] & ((board.side_to_move == white) ? ~board.occupancies[white] : ~board.occupancies[black]);

                // loop over attack squares of attack bitboard
                while (attacks.to_ullong()){
                    // init target square
                    targetSquare = indexLeastSigBit(attacks);

                    // quiet move
                    if(!board.getBit((board.side_to_move == white) ? board.occupancies[black] : board.occupancies[white], targetSquare)){
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0));
                    } else { // captures
                        add_move(move_list, encode_move(sourceSquare, targetSquare, piece, 0, 1, 0, 0, 0));
                    }

                    // pop ls1b
                    attacks.flip(targetSquare);
                }
                // pop ls1b
                bitboard.flip(sourceSquare);
            }
        }
    }
    // cout << "Total moves generated: " << m_list_of_moves->count << "\n";
    return m_list_of_moves->count;
}

// add move to move_list
void ChessGame::add_move(moves *move_list, int move){
    if(make_move(move, all_moves)){
        // store move
        move_list->moves[move_list->count] = move;

        // increment move count
        move_list->count++;

        board.restore_board();
    }
}

// short version of printing a move
void ChessGame::print_move(int move){
    cout << square_to_coordinates[get_move_source(move)] << 
            square_to_coordinates[get_move_target(move)] << 
            promoted_piece.at(get_move_promoted(move)) << 
            endl;
}

// print move list
void ChessGame::print_move_list(){
    // do nothing on empty move list
    if(!m_list_of_moves->count){
        cout << "  No move in the move list!" << endl;
    }

    printf("\n   move    piece   capture   doublePush   enpass   castling\n\n");
    // loop over moves in list
    for(int move_count=0; move_count<m_list_of_moves->count; move_count++){
        int move = m_list_of_moves->moves[move_count];
        printf("   %s%s%c   %c       %d         %d            %d        %d\n", 
                square_to_coordinates[get_move_source(move)], 
                square_to_coordinates[get_move_target(move)],
                get_move_promoted(move) ? promoted_piece.at(get_move_promoted(move)) : ' ',
                piece_to_char.at(get_move_piece(move)),
                (get_move_capture(move)) ? 1:0, 
                (get_move_doublePush(move)) ? 1:0,
                (get_move_enpassant(move)) ? 1:0,
                (get_move_castling(move)) ? 1:0);
    }

    // print total number of moves
    printf("Total number of moves: %d\n\n", m_list_of_moves->count);
}

int ChessGame::make_move(int move, int move_flag){
    // quiet moves
    if(!move_flag){     // if move_flag is equal to 0 or 'all_moves' enum
        // preserve board state for later restoring in case move is illegal
        board.copy_board();

        // parse move
        int source_square = get_move_source(move);
        int target_square = get_move_target(move);
        int piece = get_move_piece(move);
        int promoted = get_move_promoted(move);
        int capture = get_move_capture(move);
        int doublePush = get_move_doublePush(move);
        int enpass = get_move_enpassant(move);
        int castle = get_move_castling(move);

        // move piece
        board.bitboards[piece][source_square].flip();
        board.bitboards[piece][target_square].flip();

        if(capture){
            if(!board.side_to_move){        // white
                for(int piece=p; piece<=k; piece++){
                    // if bit is occupied by piece, flip it
                    if(board.getBit(board.bitboards[piece], target_square)){
                        board.bitboards[piece][target_square].flip();
                        break;
                    }
                }
            }else{                          // black
                for(int piece=P; piece<p; piece++){
                    // if bit is occupied by piece, flip it
                    if(board.getBit(board.bitboards[piece], target_square)){
                        board.bitboards[piece][target_square].flip();
                        break;
                    }
                }
            }
        }

        // handle pawn promotions
        if(promoted){
            // change piece
            board.bitboards[piece][target_square].flip();
            board.bitboards[promoted][target_square].flip();
        }

        // handle enpassant captures
        if(enpass){
            (!board.side_to_move) ? board.bitboards[p][target_square + 8].flip() : board.bitboards[P][target_square - 8].flip();
        }

        // reset enpassant square
        board.enpassant_square = no_sq;

        // handle double pawn push
        if(doublePush){
            board.enpassant_square = (!board.side_to_move) ? target_square + 8 : target_square - 8;
        }

        // handle castle move
        if(castle){
            switch (target_square)
            {
            case g1:
                // white castle king side
                board.bitboards[R][h1].flip();
                board.bitboards[R][f1].flip();
                break;
            case c1:
                // white castle queen side
                board.bitboards[R][a1].flip();
                board.bitboards[R][d1].flip();
                break;
            case g8:
                // black castle king side
                board.bitboards[r][h8].flip();
                board.bitboards[r][f8].flip();
                break;
            case c8:
                // black castle queen side
                board.bitboards[r][a8].flip();
                board.bitboards[r][d8].flip();
                break;
            
            default:
                break;
            }
        } 
        // update castling rights
        /*
                                                castling    move      in         in 
                                                rights      update    binary     decimal

            king & rooks haven't moved:         1111    &    1111  =  1111  -->  15

                      white king moved:         1111    &    1100  =  1100  -->  12
               white king's rook moved:         1111    &    1110  =  1110  -->  14
              white queen's rook moved:         1111    &    1101  =  1101  -->  13

                      black king moved:         1111    &    0011  =  0011  -->  3
               black king's rook moved:         1111    &    1011  =  1011  -->  11
              black queen's rook moved:         1111    &    0111  =  0111  -->  7

        */

        // update castling rights
        board.castling_rights &= castle_rights[source_square];
        board.castling_rights &= castle_rights[target_square];

        //-------------update occupancy boards
        // clear boards
        board.occupancies[white].reset();
        board.occupancies[black].reset();
        board.occupancies[both].reset();
        // loop over pieces to create occupancy boards
        for(int i=P; i<=K; i++){
            board.occupancies[white] |= board.bitboards[i];
            board.occupancies[black] |= board.bitboards[i + 6];
        }
        // reset occupancies
        board.occupancies[both] |= board.occupancies[white]; 
        board.occupancies[both] |= board.occupancies[black];

        //-------------check if king is in check (distinguishing between pseudo-legal and legal move)
        // change sides
        board.side_to_move ^= 1;

        // make sure that the king has not been exposed
        if(is_square_attacked((!board.side_to_move) ? indexLeastSigBit(board.bitboards[k]) : indexLeastSigBit(board.bitboards[K]), board.side_to_move)){
            // move is illegal; restore board
            board.restore_board();
            return 0;
        }else{
            board.findPieces();
            return 1;
        }

    }else{      // captures
        if(get_move_capture(move)){
            make_move(move, all_moves);
        }else return 0;
    }
    return 0;
}

int ChessGame::time_in_ms(){
    timeval time;
    gettimeofday(&time,NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

long ChessGame::PERFT_Driver(int depth){
    moves move_list[1];
    long moveNum = generateMoves(move_list);
    long nodes = 0;
    
    // exit condition
    if(depth == 1){
        return moveNum;
    }

    for(int i=0; i<m_list_of_moves->count; i++){
        board.copy_board();
        make_move(move_list->moves[i], all_moves);
        nodes += PERFT_Driver(depth - 1);
        board.restore_board();
    }
    return nodes;
}
/**********************************\
 ==================================
             Drawing
 ==================================
\**********************************/
void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(board);
}