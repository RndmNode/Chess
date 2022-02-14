# Chess Engine with SFML Graphics
> Playable Chess Engine via SFML
_
## Engine Structure

- PieceTexture Class
    - Holds the images for the piece textures
- Piece Class
    - Instances of each piece are made up from this class
    - Piece class holds the type, color, and position of the object
- Board Class
    - Holds bitboard representations of the game states
    - Sets the position of each piece based on the bitboards
- ChessGame Class
    - Holds an instance of the board class
    - Handles all game logic
    - Generates squares that each piece attacks
    - Evaluates game score
    - Holds AI functionality 
_
## Main Data Structures

### Bitboards

These are 64-bit integer representations of different aspects of the game state. Each bit represents a square
on the chess board. A '0' represents and empty square and a '1' respresents an occupied square.

### FEN String (Forsyth-Edwards Notation)

String representation of the game state.


Starting FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
'''
╔═╤═╤═╤═╤═╤═╤═╤═╗╮
║♜│♞│♝│♛│♚│♝│♞│♜║8
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║♟│♟│♟│♟│♟│♟│♟│♟║7
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║ │░│ │░│ │░│ │░║6
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║░│ │░│ │░│ │░│ ║5
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║ │░│ │░│ │░│ │░║4
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║░│ │░│ │░│ │░│ ║3
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║♙│♙│♙│♙│♙│♙│♙│♙║2
╟─┼─┼─┼─┼─┼─┼─┼─╢┊
║♖│♘│♗│♕│♔│♗│♘│♖║1
╚═╧═╧═╧═╧═╧═╧═╧═╝┊
╰a┈b┈c┈d┈e┈f┈g┈h┈╯
'''
_
## Game Setup

1) Creating an instance of ChessGame
    a. This class creates its own instance of a board object
        i.      Board constructor creates all starting pieces
        ii.     Creates all squares for visual representation of the chess board
        iii.    Parses out the starting FEN string (see above)
2) Calling init_all() on the chess game instance
    a. Calculates all squares being attacked by respective pieces
    b. Generates a list of every possible move given the game state
3) Start game loop

_
## Artificial Intelligence 

Explanation of the Negamax algorithm