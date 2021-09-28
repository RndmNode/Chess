#include "Headers/Board.h"

using namespace std;

const BITBOARD not_a_file = 18374403900871474942ULL;
const BITBOARD not_h_file = 9187201950435737471ULL;
const BITBOARD not_gh_file = 4557430888798830399ULL;
const BITBOARD not_ab_file = 18229723555195321596ULL;

const char *square_to_coordinates[] = {
                   "a8","b8","c8","d8","e8","f8","g8","h8",
                   "a7","b7","c7","d7","e7","f7","g7","h7",
                   "a6","b6","c6","d6","e6","f6","g6","h6",
                   "a5","b5","c5","d5","e5","f5","g5","h5",
                   "a4","b4","c4","d4","e4","f4","g4","h4",
                   "a3","b3","c3","d3","e3","f3","g3","h3",
                   "a2","b2","c2","d2","e2","f2","g2","h2",
                   "a1","b1","c1","d1","e1","f1","g1","h1", "no_sq"};

struct color{
    int r;
    int g;
    int b;
};
color light = {255, 248, 227}; //light squares
color dark = {122, 109, 94};   //dark squares

Board::Board(int width, int height){
    window_w = width;
    window_h = height;

    // initializing boards and pieces
    BITBOARD temp;
    temp.all();
    for(int i=0; i<12; i++){
        bitboards.push_back(temp);
        if(i<3) occupancies.push_back(temp);
    }

    // set starting FEN and parse
    // "r3k2r/p1ppqpb1/1n2pnp1/3PN3/1p2P3/2N2Q1p/PPPBqPPP/R3K2R w KQkq - 0 1"
    FEN = START_POSITION;
    parseFen(FEN);

    // white Pawns
    for(int w=0; w<8; w++){
        pieces.push_back(Piece(P, true));
    }
    // white Knights
    for(int w=0; w<2; w++){
        pieces.push_back(Piece(N, true));
    }
    // white Bishops
    for(int w=0; w<2; w++){
        pieces.push_back(Piece(B, true));
    }
    // white Rooks
    for(int w=0; w<2; w++){
        pieces.push_back(Piece(R, true));
    }
    pieces.push_back(Piece(Q,true));
    pieces.push_back(Piece(K,true));

    // black Pawns
    for(int w=0; w<8; w++){
        pieces.push_back(Piece(P, false));
    }
    // black Knights
    for(int w=0; w<2; w++){
        pieces.push_back(Piece(N, false));
    }
    // black Bishops
    for(int w=0; w<2; w++){
        pieces.push_back(Piece(B, false));
    }
    // black Rooks
    for(int w=0; w<2; w++){
        pieces.push_back(Piece(R, false));
    }
    pieces.push_back(Piece(Q,false));
    pieces.push_back(Piece(K,false));

    for(unsigned long int i=0; i<pieces.size(); i++){
        pieces[i].setTexture();
    }

    pieceOffset = pieces[0].m_sprite.getOrigin();
    
    loadBoard(width, height);
    findPieces();
}

void Board::loadBoard(int width, int height){
    float rectX = (width / 8.0f);
    float rectY = (height / 8.0f);

    // setting square sizes equal to width & height / 8
    for(int i=0; i<64; i++){
        rectangles[i].setSize(sf::Vector2f(rectX, rectY));
    }

    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            color c = (file + rank) % 2 == 0 ? light : dark;
            rectangles[file + (rank*8)].setFillColor(sf::Color(c.r, c.g, c.b));
            rectangles[file + (rank*8)].setPosition(sf::Vector2f(rectX * file, rectY * rank));
        }
    }
}

int Board::getBit(BITBOARD board, int index){
    string str = board.to_string();
    return int(str[64 - index - 1] - '0');
}

void Board::findPieces(){
    // loop through all pieces to reset their m_updated bool
    for(int i=0; i<32; i++){
        pieces[i].m_updated = false;
    }

    // loop through ranks and files
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            int index = (rank*8) + file;
            // loop through all white bitboards
            for(int _board=P; _board<p; _board++){
                // check bit at index for occupancy of piece
                if(getBit(bitboards[_board], index) == 1){
                    placePiece(_board, sf::Vector2f(file, rank), white);
                }
            }
            // loop over all black bitboards
            for(int _board=p; _board<=k; _board++){
                int b = _board - 6;
                // check bit at index for occupancy of piece
                if(getBit(bitboards[_board], index) == 1){
                    placePiece(b, sf::Vector2f(file, rank), black);
                }
            }
        }
    }
}

void Board::placePiece(int type, sf::Vector2f square, int color){
    sf::Vector2f pos = sf::Vector2f((square.x * int(rectangles[0].getSize().x)) + (int(rectangles[0].getSize().x)/2), 
                                    (square.y * int(rectangles[0].getSize().y)) + (int(rectangles[0].getSize().y)/2));

    // check for color of piece to edit
    if(color == white){
        // loop through pieces to find which to edit
        for(int i=0; i<16; i++){
            // check type
            if(pieces[i].m_type == type){
                //check updated
                if(!pieces[i].m_updated){
                    pieces[i].m_updated = true;
                    pieces[i].m_sprite.setPosition(pos);
                    pieces[i].m_squarePosition = (square.x * 8) + square.y;
                    break;
                }
            }
        }
    }else{
        // loop through pieces to find which to edit
        for(int i=16; i<32; i++){
            // check type
            if(pieces[i].m_type == type){
                //check updated
                if(!pieces[i].m_updated){
                    pieces[i].m_updated = true;
                    pieces[i].m_sprite.setPosition(pos);
                    pieces[i].m_squarePosition = (square.x * 8) + square.y;
                    break;
                }
            }
        }
    }
}

// Temp debugging bitboard printer
void Board::printBoard(int board){
    std::cout << "\n\n";
    for(int rank=0; rank<8; rank++){
        for (int file=0; file<8; file++){
            std::cout << " " << bitboards[board][(rank * 8) + file] << " ";
        }
        std::cout << "\n";
    }
}

// bitboard visualization
void Board::printBitboard(BITBOARD bitboard){
    for(int rank=0; rank<8; rank++){
        cout << "\n  " << 8- rank << "  ";
        for(int file=0; file<8; file++){
            cout << bitboard[(rank * 8) + file] << " ";
        }
    }
    cout << "\n\n     a b c d e f g h";
    cout << "\n  -------------------";
    cout << "\n  Value: " << bitboard.to_ullong() << endl;
}

void Board::parseFen(string fen){
    // reset game variables
    for(int i=0; i<12; i++){
        bitboards[i].reset();
    }
    side_to_move = -1;
    enpassant_square = no_sq;
    castling_rights = 0;

    int index = 0;
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            int square = (rank*8) + file;
            // if it is a piece, set the bit on the corresponding bitboard
            if((fen[index] >= 'a' && fen[index] <= 'z') || (fen[index] >= 'A' && fen[index] <= 'Z')){
                int piece = char_to_piece.at(fen[index]);
                bitboards[piece].set(square);
                index++;
                continue;
            }

            // if it is a number, adjust file index
            if(fen[index] >= '0' && fen[index] <= '9'){
                int offset = fen[index] - '0';
                file += offset - 1;
                index++;
                continue;
            }
            // if it's next rank, adjust indicies accordingly
            if(fen[index] == '/'){
                index++;
                file--;
                continue;
            }
        }
    }

    // isolate game state from position
    int variables = fen.find_first_of(" ") + 1;
    string variable_settings = fen.substr(variables,fen.size()-variables);

    // set game state variables
    side_to_move = (variable_settings[0] == 'w') ? white : black;

    index = 2;
    while(variable_settings[index] != ' '){
        switch (variable_settings[index])
        {
        case 'K': castling_rights |= wk; break;
        case 'Q': castling_rights |= wq; break;
        case 'k': castling_rights |= bk; break;
        case 'q': castling_rights |= bq; break;
        default:break;
        }
        index++;
    }

    index++;
    if(variable_settings[index] != '-'){
        int file = variable_settings[index] -'a';
        int rank = 8 - (variable_settings[++index] - '0');

        enpassant_square = (rank*8) + file;
    }else{
        enpassant_square = no_sq;
    }

    // init occupancy boards
    for(int piece=P; piece<=K; piece++){
        occupancies[white] |= bitboards[piece];
        occupancies[black] |= bitboards[piece + p];
    }
    occupancies[both] |= (occupancies[white] | occupancies[black]);
}

// preserve board state for undoing moves if illegal
void Board::copy_board(){
    bitboards_copy = bitboards;
    occupancies_copy = occupancies;
    side_copy = side_to_move;
    enpass_copy = enpassant_square;
    castle_copy = castling_rights;
}

// restore previous board state if illegal move was tried
void Board::restore_board(){
    bitboards = bitboards_copy;
    occupancies = occupancies_copy;
    side_to_move = side_copy;
    enpassant_square = enpass_copy;
    castling_rights = castle_copy;
    findPieces();
}

/**********************************\
 ==================================
             Drawing
 ==================================
\**********************************/
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(auto &i : rectangles) target.draw(i);
    
    int selected = 0;
    int iter = 0;
    for(auto &i : pieces){
        if(!i.m_selected){
            if(i.m_updated){
                target.draw(i);
            }
        }else selected = iter;
        iter++;
    }
    target.draw(pieces[selected]);
}