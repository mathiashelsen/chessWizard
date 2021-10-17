# chessWizard
A Chess Game for the C64

# Memory Map
* [0x00FF:0x0000] : Local variables
  * [0x001F:0x0010] : Function arguments
  * [0x002F:0x0020] : Pointer composition

* [0x1000:0x1FFF] : Piece list
* [0x2000:0x2800] : 
  * [0x2000:0x27FF] : Character RAM (0b100)
  * [0x2800:0x2BFF] : Screen RAM (0b1010)

* [0xC000:0xFFFF] : Program code

# Piece Encoding
Each piece has the following information

[7:5] Status  (active, idle, ...)
[4]   Color   (black = 0, white = 1)
[3:0] Type    (pawn = 0, knight = 1, ...)

[7:0] Position, column
[7:0] Position, row

3 Bytes for each piece, with 32 pieces makes 96 bytes of memory required for each possible board.
