#include "Headers/ChessGame.h"

using namespace std;

int width = 800;
int height = 800;

bool dragging, moving = false;
float mouseX = 0.0f;
float mouseY = 0.0f;

// move information variables
int sourceSquare, targetSquare, piece, _move;

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
                    if(!moving){
                        piece = (i.m_player) ? i.m_type : i.m_type + 6;
                        sourceSquare = i.getPosition(window, sf::Vector2f(mouseX, mouseY));
                        cout << "\nsource: " << square_to_coordinates[sourceSquare] << endl;
                    }
                    i.m_sprite.setPosition(mouseX, mouseY);
                    moving = true;
                    break;
                }
            }
        }else{
            for(auto &i :chess.board.pieces){
                if(i.m_selected){
                    targetSquare = i.getPosition(window, sf::Vector2f(mouseX, mouseY));
                    i.setPosition(window, sf::Vector2f(mouseX, mouseY));
                    i.m_selected = false;
                    cout << "\nsource: " << square_to_coordinates[sourceSquare] << endl;
                    cout << "target: " << square_to_coordinates[targetSquare] << endl;
                    cout << "piece: " << piece_to_char.at(piece) << endl;
                    _move = encode_move(sourceSquare, targetSquare, piece, 0, 0, 0, 0, 0);
                    chess.make_move(_move, all_moves);
                    printFullCharBoard(chess.board);
                    sourceSquare = -1, targetSquare = -1, piece = -1, _move = -1;
                    moving = false;
                }
            }
        }

        // clear and draw screen
        window.clear();
        window.draw(chess);
        window.display();
    }
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
    int sourceSquare;
    int end = chess.m_list_of_moves->count;
    // int move = 0;
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
                    if(i<end){
                        if(!rest){
                            sourceSquare = get_move_source(chess.m_list_of_moves->moves[i]);
                            chess.board.rectangles[sourceSquare].setFillColor(sf::Color::Red);
                            chess.make_move(chess.m_list_of_moves->moves[i], all_moves);
                            cout << "size: " << chess.move_history.size() << "    top: " << chess.move_history.top() << endl;
                            rest = true;
                        }else{
                            chess.undo_move();
                            chess.board.loadBoard(width, height);
                            i++;
                            rest = false;
                        }
                    }else{
                        if(j>0) chess.undo_move();
                        chess.board.loadBoard(width, height);
                        i=0;
                        sourceSquare = get_move_source(move_list->moves[j]);
                        chess.board.rectangles[sourceSquare].setFillColor(sf::Color::Green);
                        chess.make_move(move_list->moves[j], all_moves);
                        j++;
                        chess.generateMoves(chess.m_list_of_moves);
                        end = chess.m_list_of_moves->count;
                    }
                    break;

                case sf::Mouse::Right:
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
}

int main(){ 
    game();
    // move();

    return 0;
}