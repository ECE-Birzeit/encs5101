; asm.S: LED on pin 13 (PB7) follows the button on pin 4 (PG5)
; Button between pin 4 and GND, with the internal pull-up:
; released reads 1, pressed reads 0.

#define __SFR_OFFSET 0
#include <avr/io.h>

.global start
.global update

start:
  sbi DDRB, 7                   ; PB7 output (LED)
  cbi DDRG, 5                   ; PG5 input (button)
  sbi PORTG, 5                  ; PG5 is an input, so this turns on its pull-up
  ret

update:
  sbis PING, 5                  ; skip the next line if PG5 reads 1 (released)
  rjmp pressed                  ; PG5 reads 0: pressed
  cbi PORTB, 7                  ; released: LED off
  ret
pressed:
  sbi PORTB, 7                  ; pressed: LED on
  ret
