# chessWizard
A Chess Game for the C64

# Memory Map
* [0x00FF:0x0000] : Local variables
  * [0x001F:0x0010] : Function arguments
  * [0x002F:0x0020] : Pointer composition

* [0x1000:0x1FFF] : Piece list, score, current player, moves list
* [0x6000:0x6800] : 
  * [0x6000:0x67FF] : Character RAM (0b100)
  * [0x6800:0x6BFF] : Screen RAM (0b1010)

* [0xC000:0xFFFF] : Program code

# Piece Encoding
Each piece has the following information

Byte 0

[7:5] Status  (active, idle, ...)

[4]   Color   (black = 0, white = 1)

[3:0] Type    (pawn = 0, knight = 1, ...)

Byte 1

[7:0] Value   (pawn = 1, knight = 3, ...)


Byte 2 

[7:0] Position, column


Byte 3

[7:0] Position, row

4 Bytes for each piece, with 32 pieces makes 128 bytes of memory required for each possible board.
We will probably require two boards: one actual, one where the computer experiments with moves.
A routine will be needed to move from one board to another via a list of moves.

# Move Encoding
First byte: selects piece [0..32]
Second byte: gain/loss
Third, fourth byte: new position column, row respectively


# Functions

CopyBoard:
  Copies current board into the experimenting board
  Input: Starting board

ExecuteMoves:
  Input: Starting board
  Input: MovesList
  Input: Number of moves
  Output: New board

ComputerMakeMove:
  AI solves for a good solution (loads Chess Engine)

HumanMakeMove:
  A lot of keyboard interaction
