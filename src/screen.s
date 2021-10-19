!zone screen

dest_ptr  = $10
src_ptr   = $12
line_ctr  = $14

initScreen:
  jsr .copyCharset
  jsr .initMemory
  jsr .setCheckerboard
  jsr clearScreen
  rts

.initMemory:
  ;; Set the background colors
  lda #$00
  sta $d021
  lda #$01
  sta $d022
  lda #$06
  sta $d023
  lda #$07
  sta $d024

  ;; Set multicolor mode
  lda #$10
  sta $d016

  ;; Set memory setup
  lda #%10101000
  sta $d018
  lda #$02
  sta $dd00

.screenPtr  = $10

.colorA     = $12
.colorB     = $13
.colorTmp   = $14

.setCheckerboard
  lda #$06
  sta .colorA
  lda #$0e
  sta .colorB
  lda #$00
  sta .screenPtr
  lda #$d8
  sta .screenPtr+1
  ldx #$00
  ldy #$00
- lda .colorA
  sta (.screenPtr),y
  iny
  lda .colorB
  sta (.screenPtr),y
  iny
  cpy #$08
  bne -
  ldy #$00
  clc
  lda .screenPtr
  adc #$28
  sta .screenPtr
  lda .screenPtr+1
  adc #$00
  sta .screenPtr+1
  inx
  lda .colorB
  sta .colorTmp
  lda .colorA
  sta .colorB
  lda .colorTmp
  sta .colorA
  cpx #$08
  bne -
  rts

.copyCharset:
  lda #<charset
  sta src_ptr
  lda #>charset
  sta src_ptr+1
  lda #$00
  sta dest_ptr
  lda #$60
  sta dest_ptr+1
  ldx #$00
  ldy #$00
  lda #$00
  sta line_ctr

.copyLine:
  lda (src_ptr) , y
  sta (dest_ptr), y
  inx
  iny
  cpx #$10          ;; Copy 16 entries
  bne .copyLine

  cpy #$00          ;; Check for overflow on y
  bne .nextPage
  inc src_ptr +1    ;; On overflow, increase the pointer MSB
  inc dest_ptr+1
  

.nextPage:
  inc line_ctr
  lda line_ctr
  cmp 128
  beq .copyDone
  ldx #$00
  jmp .copyLine

.copyDone:
  rts


.screen_lb             = $54   ;; Both are used in the (ZP),y addressing mode
.screen_hb             = $55   ;; to compose the screen RAM address
.screen_base           = $60   ;; We alternate between 0x400 and 0x800

clearScreen:
  lda #$68
  sta .screen_base
  lda #$00
  sta .screen_lb
  lda .screen_base
  sta .screen_hb

  ldx #$00
.clear_screen_loop:
  jsr .clear_row_start
  clc
  lda .screen_lb
  adc #$28
  sta .screen_lb
  lda .screen_hb
  adc #$00
  sta .screen_hb
  inx
  cpx #$19
  bne .clear_screen_loop
  rts

.clear_row_start:
  ldy #$00
  lda #$56
.clear_row:
  sta (.screen_lb),y
  iny
  cpy #$29
  bne .clear_row
  rts

!source "charset.s"
