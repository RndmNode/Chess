# Chess Engine with SFML Graphics
> Playable Chess Engine via SFML

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

## Main Data Structures

### Bitboards | Board representation

These are 64-bit binary representations of piece placement with each bit represents a square on the chess board. A '0' represents and empty square and a '1' respresents an occupied square. Because these data structures are effectively integers, they take up less memory and, as a result, are able to be referenced and manipulated efficiently.

However, because not every piece can be represented with a '1' or a '0', the piece types and colors all have their own 'binary' representation given the game state. In other words, the white pawns have their own bitboard, the black knights the their own, the white king has its own, etc. etc. We use these bitboard (with a combination of many other bitboards) to find out many things about the game. These bitboards are used in game score/evaluation, which piece is attacking which, check and checkmate, and more.

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

#### Examples:

Starting position FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
![alt text](https://images.chesscomfiles.com/uploads/v1/images_users/tiny_mce/pdrpnht/phprLkH4s.png)

FEN: "8/5k2/3p4/1p1Pp2p/pP2Pp1P/P4P1K/8/8 b - - 99 50"
![alt text](https://images.chesscomfiles.com/uploads/v1/images_users/tiny_mce/pdrpnht/phpllS96z.png)

For more detailed information on FEN Strings, [follow this link.](https://www.chessprogramming.org/Forsyth-Edwards_Notation)
Or here is a [nice and easy explanation.](https://www.chess.com/terms/fen-chess)

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

## Artificial Intelligence 

The chose algorithm for this engine is the [Negamax Algorithm.](https://en.wikipedia.org/wiki/Negamax)

The Negamax algorithm operates like a game tree. Each node in the tree represents a game state after a given possible move. Prior to building the game tree, the engine has to calculate and store all possible moves given a state and depth for how many possible moves into the future it should look.

After generating all moves, the engine has to walk through each move and score that move based on the board state. From there, the algorithm traverses down the tree to find the next best move based on trying to maximize the score for the player that has the next move and minimizing the score for the opposing player. 

[Here is an informative animation on how it works.](https://en.wikipedia.org/wiki/Negamax#/media/File:Plain_Negamax.gif)