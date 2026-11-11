; asm.S: Lab work 2. Fill in the three TODOs.
; LED A = PA3 (pin 25), LED B = PA5 (pin 27), button = PA1 (pin 23)
; Released: LED A on, LED B off. Pressed: LED B on, LED A off.

#define __SFR_OFFSET 0
#include <avr/io.h>

.global start
.global update

start:
  sbi DDRA, 3                   ; PA3 output (LED A)
  sbi DDRA, 5                   ; PA5 output (LED B)
  cbi DDRA, 1                   ; PA1 input (button)
  ; TODO 1: turn on the pull-up of PA1
  ret

update:
  sbis PINA, 1                  ; skip the next line if PA1 reads 1 (released)
  rjmp pressed
  ; TODO 2: released: LED A on, LED B off (two lines)
  ret
pressed:
  ; TODO 3: pressed: LED B on, LED A off (two lines)
  ret
