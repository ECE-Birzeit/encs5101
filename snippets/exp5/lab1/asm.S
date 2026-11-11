; asm.S: Lab work 1. Fill in the three TODOs.
; LED A = PA0 (pin 22), LED B = PA1 (pin 23)

#define __SFR_OFFSET 0
#include <avr/io.h>

.global start
.global show

start:
  sbi DDRA, 0                   ; PA0 output
  ; TODO 1: make PA1 an output too
  ret

show:                           ; "which" arrives in r24
  cpi r24, 0
  breq showA                    ; which = 0: jump to showA
  cbi PORTA, 0                  ; which = 1: LED A off
  ; TODO 2: LED B on
  ret
showA:
  ; TODO 3: LED A on, LED B off (two lines)
  ret
