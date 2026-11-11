; asm.S: turn the on-board LED (pin 13 = PB7) on and off

; Names such as DDRB, as I/O addresses.
; Never put a comment on the next two lines.
#define __SFR_OFFSET 0
#include <avr/io.h>

.global start                   ; make the functions visible to blink.ino
.global led

start:
  sbi DDRB, 7                   ; bit 7 of DDRB = 1: PB7 is an output
  ret                           ; back to setup()

led:                            ; the argument "on" arrives in r24
  cpi r24, 0                    ; compare r24 with 0
  breq off                      ; equal: jump to off
  sbi PORTB, 7                  ; not 0: PB7 HIGH, LED on
  ret                           ; back to loop()
off:
  cbi PORTB, 7                  ; PB7 LOW, LED off
  ret
