# chessWizard
A Chess Game for the C64

# Memory Map
* [0x00FF:0x0000] : Local variables
  * [0x001F:0x0010] : Function arguments
  * [0x002F:0x0020] : Pointer composition

* [0x1000:0x1FFF] : Piece list
* [0xFFFF:0xC000] : Swap-out kernal (HIRAM = 0)
  * [0xF000:0xF7FF] : Character RAM (0b110)
  * [0xF800:0xFBFF] : Screen RAM (0b1110)

* [0x2000:0xD000] : Program code
