#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

bool dragging = false;
float mouseX = 0.0f;
float mouseY = 0.0f;

sf::Vector2f traslateToSquare(sf::Vector2f pos, sf::RenderTarget &target){
    int windowX = target.getSize().x;
    int windowY = target.getSize().y;

    int side_x = windowX/8;
    int side_y = windowY/8;

    int x_boardPos = pos.x/side_x;
    int y_boardPos = pos.y/side_y;

    int x = (x_boardPos * side_x) + (side_x / 2);
    int y = (y_boardPos * side_y) + (side_y / 2);

    return sf::Vector2f(x, y);
}

void game() {
    sf::RenderWindow window;

    window.create(sf::VideoMode(width, height), "CHESS!");
    ChessGame chess(window);
    // run the program as long as the window is open
    while(window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while(window.pollEvent(event)){
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                switch (event.key.code)
                {
                case sf::Mouse::Left:
                    dragging = true;
                    for(auto &i : chess.board.pieces){
                        if(i.m_sprite.getGlobalBounds().contains(mouseX, mouseY)){
                            i.m_selected = true;
                            break;
                        }else i.m_selected = false;
                    }
                    break;
                //-------
                default:
                    break;
                //-------
                }
                break;
            
            case sf::Event::MouseButtonReleased:
                switch (event.key.code)
                {
                case sf::Mouse::Left:
                    dragging = false;
                    break;
                //-------
                default:
                    break;
                //-------
                }
                break;
            
            case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                break;

            //-------
            default:
                break;
            //-------
            }
        }

        if(dragging){
            for(auto &i : chess.board.pieces){
                if(i.m_selected){
                    i.m_sprite.setPosition(mouseX,mouseY);
                    break;
                }
            }
        }else{
            for(auto &i :chess.board.pieces){
                if(i.m_selected){
                    i.setPosition(window, sf::Vector2f(mouseX, mouseY));
                    i.m_selected = false;
                }
            }
        }

        // clear and draw screen
        window.clear();
        window.draw(chess);
        window.display();
    }
}

// FEN parsing debugger
void printFullCharBoard(Board board){
    char fullBoard[64];
    bool occupied;

    // loop through the squares
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            int square = (rank*8)+file;
            occupied = false;

            // loop through the boards to check bits
            for(int i=P; i<=k; i++){
                int bit = board.getBit(board.bitboards[i], square);
                if(bit == 1){
                    occupied = true;
                    fullBoard[square] = piece_to_char.at(i);
                    break;
                }
            }
            if(!occupied) fullBoard[square] = '.';
        }   
    }

    cout << "\nFull Board:\n ";
    for(int rank=0; rank<8; rank++){
        for(int file=0; file<8; file++){
            cout << fullBoard[(rank*8)+file];
        }
        cout << "\n ";
    }
}

// bitboard visualization
void printBitboard(BITBOARD bitboard, string name){
    int y = 8;
    cout << "\n      " << name << ":\n";
    for(int rank=0; rank<8; rank++){
        cout << "\n  " << y << "   ";
        for(int file=0; file<8; file++){
            cout << bitboard[(rank * 8) + file] << " ";
        }
        y--;
    }
    cout << "\n\n      a b c d e f g h";
    cout << "\n";
    //cout << "\n\n  value: " << bitboard.to_ullong() << endl;
}

// bitboard visualization(2)
void printBitboard(BITBOARD bitboard){
    int y = 8;
    cout << "\n\n";
    for(int rank=0; rank<8; rank++){
        cout << "\n  " << y << "   ";
        for(int file=0; file<8; file++){
            cout << bitboard[(rank * 8) + file] << " ";
        }
        y--;
    }
    cout << "\n\n      a b c d e f g h";
    cout << "\n\n  value: " << bitboard.to_ullong() << endl;
}

int main(){
    // game();
    ChessGame chess;
    chess.init_leaper_attacks();

    // for(int s=a8; s<no_sq; s++){
    //     printBitboard(chess.getRookOccupancy(s));
    // }

    BITBOARD block = 0ULL;
    block = Board::setBit(block, b4);
    block = Board::setBit(block, d7);
    block = Board::setBit(block, d3);
    block = Board::setBit(block, g4);

    printBitboard(block);
    printBitboard(chess.generateRookAttacks(d4, block));

    return 0;
}

