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
    chess.init_all();

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
                    i.m_sprite.setPosition(mouseX, mouseY);
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
                              ((board.castling_rights & bq) ? 'q' : '-' )<< '\n' << '\n';
}

void move() {
    sf::RenderWindow window;

    window.create(sf::VideoMode(width, height), "CHESS!");
    ChessGame chess(window);
    chess.init_all();

    moves move_list[1];
    chess.generateMoves(move_list);
    chess.generateMoves(chess.m_list_of_moves);

    int i=0, j=0;
    int end = chess.m_list_of_moves->count;
    int move = 0;
    bool rest = false;

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
                    // cout << "mouse left pressed.\n";
                    // cout << "i: " << i << "\n";
                    if(i < end){
                        if(!rest){
                            // cout << "i: " << i << "\n";
                            move = chess.m_list_of_moves->moves[i];
                            if(chess.make_move(move, all_moves)){
                                i++;
                                rest = true;
                                printFullCharBoard(chess.board);
                            }else{
                                i++;
                            }
                        }else{
                            // cout << "restoring board.\n";
                            chess.board.restore_board();
                            rest = false;
                            printFullCharBoard(chess.board);
                        }
                    } else {
                        chess.board.restore_board();
                        i=0;
                        chess.board.parseFen(START_POSITION);
                        move = move_list->moves[j];
                        j++;
                        chess.make_move(move, all_moves);
                        chess.generateMoves(chess.m_list_of_moves);
                    }
                    break;

                case sf::Mouse::Right:
                    i--;
                    break;
                //-------
                default:
                    break;
                //-------
                }
                break;
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
    cout << chess.m_list_of_moves->count + move_list->count << endl;
}

int main(){ 
    // game();
    // move();
    ChessGame chess;
    chess.init_all();
    moves move_list[1];

    chess.generateMoves(chess.m_list_of_moves);

    for(int i=0; i<chess.m_list_of_moves->count; i++){
        int move_1 = chess.m_list_of_moves->moves[i];
        chess.make_move(move_1, all_moves);
        chess.generateMoves(move_list);
        for(int j=0; j<move_list->count; j++){
            int move_2 = move_list->moves[j];
            chess.make_move(move_2, all_moves);
            printFullCharBoard(chess.board);
            getchar();
            chess.board.restore_board();
        }
        chess.board.restore_board();
    }

    return 0;
}