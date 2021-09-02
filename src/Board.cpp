#include <bitset>
#include <iostream>

#include "Headers/Board.h"

using namespace std;

struct color{
    int r;
    int g;
    int b;
};
color light = {255, 248, 227}; //light squares
color dark = {122, 109, 94};   //dark squares

Board::Board(int width, int height){
    // initializing boards and pieces
    bitset<64> temp;
    temp.all();
    for(int i=0; i<12; i++){
        bitboards.push_back(temp);
    }

    //set starting FEN and parse
    parseFen(START_POSITION);

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

int Board::getBit(bitset<64> board, int index){
    string str = board.to_string();
    return int(str[64 - index - 1] - '0');
}

void Board::findPieces(){
    // loop through all pieces to reset their m_updated bool
    for(int i=0; i<32; i++){
        // if not captured
        if(!pieces[i].m_captured){
            pieces[i].m_updated = false;
        }
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
    sf::Vector2f pos = sf::Vector2f(square.x * 100, square.y * 100);

    // check for color of piece to edit
    if(color == white){
        // loop through pieces to find which to edit
        for(int i=0; i<16; i++){
            // if not captured
            if(!pieces[i].m_captured){
                // check type
                if(pieces[i].m_type == type){
                    //check updated
                    if(!pieces[i].m_updated){
                        pieces[i].m_updated = true;
                        pieces[i].m_sprite.setPosition(pos);
                        break;
                    }
                }
            }
        }
    }else{
        // loop through pieces to find which to edit
        for(int i=16; i<32; i++){
            // if not captured
            if(!pieces[i].m_captured){
                // check type
                if(pieces[i].m_type == type){
                    //check updated
                    if(!pieces[i].m_updated){
                        pieces[i].m_updated = true;
                        pieces[i].m_sprite.setPosition(pos);
                        break;
                    }
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

void Board::parseFen(string fen){
    for(int i=0; i<12; i++){
        bitboards[i].reset();
    }

    int index = 0;
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            int square = (rank*8) + file;
            //cout << "fen[i]: " << fen[index] << endl;
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

            if(fen[index] == '/'){
                index++;
                file--;
                continue;
            }
            
        }
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<64; i++){
        target.draw(rectangles[i]);
    }

    for(int i=0; i<32; i++){
        if(this->pieces[i].m_updated){
            //cout << "Piece " << char(piece_to_char.at(this->pieces[i].m_type)) << " updated!\n";
        }
        if(!this->pieces[i].m_captured && this->pieces[i].m_updated){
            target.draw(this->pieces[i]);
        }
    }
}