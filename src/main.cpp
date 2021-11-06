#include <chrono>
#include <thread>

#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

bool positionChecked, dragging, prevDragging, moving = false;
float mouseX = 0.0f;
float mouseY = 0.0f;

// move information variables
int sourceSquare, targetSquare, piece;

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

    cout << "\n  Full Board:\n\n ";
    for(int rank=0; rank<8; rank++){
        cout << " " << 8 - rank << "   ";
        for(int file=0; file<8; file++){
            cout << fullBoard[(rank*8)+file] << " ";
        }
        cout << "\n ";
    }
    cout << "\n      a b c d e f g h\n\n";

    cout << "  Side: " << ((board.side_to_move) ? "black\n" : "white\n");
    cout << "  Enpassant: " << square_to_coordinates[board.enpassant_square] << endl;
    cout << "  Castling: " << ((board.castling_rights & wk) ? 'K' : '-' )<<  
                              ((board.castling_rights & wq) ? 'Q' : '-' )<<
                              ((board.castling_rights & bk) ? 'k' : '-' )<<
                              ((board.castling_rights & bq) ? 'q' : '-' )<< '\n';
    cout << "  FEN: " << board.FEN << "\n\n";
}

void game() {
    sf::RenderWindow window;
    

    window.create(sf::VideoMode(width, height), "CHESS!");
    ChessGame chess(window);
    chess.init_all();

    bool check = false;

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
                case sf::Mouse::Right:
                    chess.undo_move();
                    chess.undo_move();
                    chess.generateMoves(chess.m_list_of_moves);
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
        if(chess.board.side_to_move == white){
            if(dragging){
                for(auto &i : chess.board.pieces){
                    if(i.m_selected){
                        if(!moving){
                            piece = (i.m_player) ? i.m_type : i.m_type + 6;
                            cout << "piece: " << piece_to_char.at(piece) << endl;
                            sourceSquare = i.getPosition(window, sf::Vector2f(mouseX, mouseY));
                            cout << "source: " << square_to_coordinates[sourceSquare] << endl;
                            moving = true;
                        }
                        i.m_sprite.setPosition(mouseX, mouseY);
                        break;
                    }
                }
            }else {
                for(auto &i :chess.board.pieces){
                    if(i.m_selected){
                        targetSquare = i.getPosition(window, sf::Vector2f(mouseX, mouseY));
                        i.setPosition(window, sf::Vector2f(mouseX, mouseY));
                        chess.handle_move(sourceSquare, targetSquare, piece);
                        printFullCharBoard(chess.board);
                        sourceSquare = -1, targetSquare = -1, piece = -1;
                        i.m_selected = false, moving = false;
                    }
                }
            }
        }else {
            chess.search_position(3);
            chess.make_move(chess.m_best_move, all_moves);
            printFullCharBoard(chess.board);
            chess.generateMoves(chess.m_list_of_moves);
        }

        check = chess.is_square_attacked(((!chess.board.side_to_move) ? chess.indexLeastSigBit(chess.board.bitboards[K]) : 
                                                                        chess.indexLeastSigBit(chess.board.bitboards[k])),
                                                                        chess.board.side_to_move ^ 1);
        
        // clear and draw screen
        window.clear();
        window.draw(chess);
        window.display();

        if(check){
            if(!positionChecked){
                chess.search_position(3);
                positionChecked = true;
            }
            if(!chess.m_legal_moves_num){
                cout << "Checkmate!!!\n";
                cout << ( (!chess.board.side_to_move) ? "Black " : "White " ) << "Wins!!!\n\n";
                this_thread::sleep_for(chrono::seconds(5));
                window.close();
            }
        }else positionChecked = false;
    }
}


void test() {
    sf::RenderWindow window;

    window.create(sf::VideoMode(width, height), "CHESS!");
    ChessGame chess(window);
    chess.init_all();

    printf("\n");

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
                    chess.search_position(6);
                    chess.make_move(chess.m_best_move, all_moves);
                    break;
                case sf::Mouse::Right:
                    chess.undo_move();
                    break;
                //-------
                default:
                    break;
                }
            //-------
            default:
                break;
            //-------
            }
        }

        // clear and draw screen
        window.clear();
        window.draw(chess);
        window.display();
    }
}

int main(){ 
    game();

    return 0;
}