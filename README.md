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



For more information on bitboards, [follow this link.](https://www.chessprogramming.org/Bitboards)

### FEN String (Forsyth-Edwards Notation)

A FEN string is a string representation of the game state. The first portion, and the longest portion, of the string is the representation of the pieces and their placement. Capital letters are the white pieces, and the lowercase are the black pieces. Each slash "/" represents a break to the next rank (row) and each number represents the number of empty squares until the next rank or piece. The board is filled left-to-right just as the string is read left-to-right. 

For example, consider the following string: "R6r/4q2P/". This would represent one row having a white rook on the first square, followed by 6 empty spaces, and then a black rook. Then there is a slash "/" which represents the break to the next row, where it starts with 4 empty spaces, a black queen, 2 more empty spaces, before finishing with a white pawn. 

Following the letters and numbers that represent the pieces and placements, there is a space and either a w or b. This represents whose turn it is (w for white, b for black). After that comes the castling rights; KQkq means both players have not moved their king or either of their rooks from their starting positions, giving the king the right to castle to that side. 
- K: White king-side
- Q: White queen-side
- k: Black king-side
- q: black queen-side

After the castling rights lives the space for the en passant square (if there is one). If there is a '-' in this space, then there is no legal en passant square during that turn. The number following this is the halfmove clock, and after that is the fullmove counter.

#### Examples

Empty board FEN : "8/8/8/8/8/8/8/8 w KQkq - 0 1"

Starting position FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
![alt text](https://images.chesscomfiles.com/uploads/v1/images_users/tiny_mce/pdrpnht/phprLkH4s.png)

FEN: "8/5k2/3p4/1p1Pp2p/pP2Pp1P/P4P1K/8/8 b - - 99 50"
![alt text](https://images.chesscomfiles.com/uploads/v1/images_users/tiny_mce/pdrpnht/phpllS96z.png)

For more information on FEN Strings, [follow this link.](https://www.chessprogramming.org/Forsyth-Edwards_Notation)
Or
[Here is a nice and easy explanation](https://www.chess.com/terms/fen-chess)
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