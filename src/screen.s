!zone screen

dest_ptr  = $10
src_ptr   = $12
line_ctr  = $14

initScreen:
  jsr .copyCharset
  jsr .initMemory
  jsr .setCheckerboard
  rts

.initMemory:
  ;; Set the background colors
  lda #$04
  sta $d021
  lda #$05
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

.setCheckerboard
  lda #$00
  sta .screenPtr
  lda #$d8
  sta .screenPtr+1
  ldx #$00
  ldy #$00
  lda #$0a
- sta (.screenPtr),y
  iny
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

!source "charset.s"
