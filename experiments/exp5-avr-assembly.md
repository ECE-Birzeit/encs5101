---
title: Assembly Programming on Arduino
description: Write AVR assembly functions for the ATmega2560, call them from an Arduino sketch, and drive LEDs and read a button straight from the port registers with sbi, cbi and sbis.
short: "AVR Assembly"
manual: "/ENCS5101-Manual.pdf#page=84"
---

# Assembly Programming on Arduino

In Experiments 1 and 2 you wrote assembly for an ARM processor; in Experiment 3 you wrote C for the Arduino. This experiment joins the two. You write small **AVR assembly** functions for the Mega's ATmega2560, call them from an ordinary sketch, and control pins through the **port registers** that `pinMode()` and `digitalWrite()` use underneath.

## Objectives

- Find the port and bit behind an Arduino pin, and set it up with the `DDRx`, `PORTx` and `PINx` registers.
- Write an assembly function in a `.S` file and call it from a sketch.
- Pass a value from C to assembly in `r24`, and branch on it.
- Turn pins on and off with `sbi` and `cbi`, and read a button with `sbis`.

::: tip Before the lab
Finish [Experiment 3](./exp3-arduino-intro). You need binary and hex: bit 7 of a byte is `0b10000000`, which is `0x80`.
:::

## Background

### Registers and address spaces

The ATmega2560 is an 8-bit processor. It works on 32 general registers, `r0` to `r31`, each 8 bits wide. Like ARM, it only does arithmetic in registers, and memory is reached with load and store instructions. Unlike ARM, the result of `add r24, r22` goes back into the **first** register, `r24`.

Everything the processor can read or write has an address in one data space:

| Data address | Holds |
| --- | --- |
| `0x0000`–`0x001F` | The 32 registers `r0`–`r31` |
| `0x0020`–`0x005F` | The 64 **I/O registers**: ports A–G, timers, status |
| `0x0060`–`0x01FF` | Extended I/O: ports H–L and the other peripherals |
| `0x0200`–`0x21FF` | 8 KB of SRAM for variables |

The 64 I/O registers can also be reached through a short **I/O address**, 0x20 lower than the data address, with the fast instructions `in`, `out`, `sbi` and `cbi`. `DDRB` is data address `0x24` but I/O address `0x04`. The line `#define __SFR_OFFSET 0` at the top of each program makes names such as `DDRB` mean the I/O address, which is what those instructions expect.

### Port registers

The Mega's pins are grouped into **ports** of 8, named A to L. Each Arduino pin is one bit of one port; the [Mega pinout](./exp3-arduino-intro#the-arduino-mega-2560) labels them, as `PA0` for port A bit 0. The pins this experiment uses:

| Arduino pin | Port bit |
| --- | --- |
| 4 | `PG5`: port G, bit 5 |
| 13, the on-board LED **L** | `PB7`: port B, bit 7 |
| 22, 23, 24 … 29 | `PA0`, `PA1`, `PA2` … `PA7`: port A, bits 0–7 |

Port A is convenient: its 8 bits are 8 neighbouring header pins, and pin 22 + n is bit n.

Three registers control each port `x`, one bit per pin:

| Register | Bit = 1 | Bit = 0 |
| --- | --- | --- |
| `DDRx` (data direction) | Output | Input |
| `PORTx`, output pin | Drive `HIGH` | Drive `LOW` |
| `PORTx`, input pin | Internal pull-up on | Pull-up off |
| `PINx` (read only) | Pin reads `HIGH` | Pin reads `LOW` |

So pin 13 as an output, driven `HIGH`, is bit 7 of `DDRB` set and bit 7 of `PORTB` set: what `pinMode(13, OUTPUT)` and `digitalWrite(13, HIGH)` do for you.

### Addressing modes

The addressing mode is how an instruction finds its operand. The ones you meet on the AVR:

| Mode | Example | Effect |
| --- | --- | --- |
| Register | `inc r24` | `r24 ← r24 + 1` |
| Two registers | `add r24, r22` | `r24 ← r24 + r22` |
| Immediate | `ldi r18, 0xFF` | `r18 ← 0xFF`. Only `r16`–`r31`. |
| I/O direct | `out DDRA, r18`<br>`in r24, PINA` | Copy a register to an I/O register, or back. I/O address 0–63. |
| I/O bit | `sbi PORTB, 7` | Set or clear one bit of an I/O register. I/O address 0–31 only. |
| Data direct | `lds r24, 0x0200` | `r24 ←` the byte at data address `0x0200`. `sts` stores. |
| Indirect | `ld r24, X` | `r24 ←` the byte at the address held in `X` (`r27:r26`). Also `Y` and `Z`. |
| Indirect, post-increment | `ld r24, X+` | The same, then `X ← X + 1`: steps through an array. |

`X`, `Y` and `Z` are the register pairs `r27:r26`, `r29:r28` and `r31:r30`, used together as 16-bit addresses.

::: warning Ports H to L are out of reach
Ports A–G sit at I/O addresses below 32, so `sbi`, `cbi` and `sbis` work on them. Ports H–L are extended I/O and need `lds` and `sts`. That rules out pins 6–9, among others; this experiment uses only pins on ports A, B and G.
:::

### Calling assembly from a sketch

A sketch with assembly in it has two files in one folder: the usual `.ino`, and a `.S` file with the assembly. The `.ino` declares the assembly functions inside `extern "C"` and calls them like any other function:

```cpp
extern "C" {
  void start();         // written in asm.S
  void led(byte on);
}
```

The `.S` file marks each function `.global`, so the `.ino` can find it, and starts it with a label of the same name. Each function ends with `ret`, which returns to the line after the call. Comments start with `;`.

The C compiler and your assembly share the registers, so follow its rules:

| Register | Rule |
| --- | --- |
| `r24` | Holds the first `byte` argument when the function starts. A `byte` result goes back in `r24`. |
| `r18`–`r27`, `r30`, `r31` | Free to use. |
| `r1` | Leave alone: C expects it to be 0. |
| `r2`–`r17`, `r28`, `r29` | Belong to the caller. Save them with `push` and restore with `pop` if you use them. |

### The instructions used here

| Instruction | Effect |
| --- | --- |
| `sbi P, b` | Set bit `b` of I/O register `P` to 1 |
| `cbi P, b` | Clear bit `b` of I/O register `P` to 0 |
| `sbis P, b` | Skip the next instruction if bit `b` of `P` is 1 |
| `sbic P, b` | Skip the next instruction if bit `b` of `P` is 0 |
| `ldi r, K` | Load the constant `K` into `r` (`r16`–`r31`) |
| `out P, r` / `in r, P` | Copy a whole byte to or from I/O register `P` |
| `cpi r, K` | Compare `r` with the constant `K`, setting the flags (`r16`–`r31`) |
| `breq label` / `brne label` | Branch if the last compare was equal / not equal |
| `rjmp label` | Jump |
| `ret` | Return from the function |

`sbi DDRB, 7` changes only bit 7. `ldi r18, 0x80` then `out DDRB, r18` also makes PB7 an output, but writes all 8 bits, so every other pin of port B becomes an input.

## Materials

- Arduino Mega 2560 and USB cable
- Breadboard and jumper wires
- 2 LEDs and 2 × 220 Ω resistors
- Push button

## Examples

### Make a sketch with an assembly file

Do this once for each example and lab work:

1. In the Arduino IDE, create a new sketch and save it, for example as `blink`.
2. Click the **three dots** at the right end of the tab bar, choose **New Tab**, and name it `asm.S`. The **S must be a capital**: a lower-case `.s` file is ignored, and the sketch fails with "undefined reference".
3. Paste the `.ino` code into the first tab and the assembly into `asm.S`, then upload as usual.

### Example 1: blink from assembly

No wiring: this uses the on-board LED on pin 13, `PB7`.

<<< @/snippets/exp5/blink/blink.ino{cpp}

<<< @/snippets/exp5/blink/asm.S{asm}

The LED blinks, on 200 ms and off 200 ms. `loop()` calls `led(1)`, so `r24` is 1: `cpi` finds it is not 0, `breq` does not jump, and `sbi` turns the LED on. `led(0)` makes `breq` jump to `off`, and `cbi` turns it off.

### Example 2: LED follows a button

Wire a push button between pin 4 (`PG5`) and GND. The internal pull-up holds the pin at 1 until you press it.

<<< @/snippets/exp5/button/button.ino{cpp}

<<< @/snippets/exp5/button/asm.S{asm}

The LED is on while you hold the button and off when you let go. `sbis` is the assembly form of `if`: when the pin reads 1 it skips `rjmp pressed` and falls into the "released" lines.

## Lab work

Each lab work starts from a sketch that already works except for a few lines marked `TODO`, all in `asm.S`. Copy both files into the IDE, fill in the TODOs, and upload.

### Lab work 1: two LEDs take turns

LED A is on for 1 s while LED B is off, then they swap, and so on.

Wire LED A to pin 22 (`PA0`) and LED B to pin 23 (`PA1`), each through 220 Ω to GND.

<<< @/snippets/exp5/lab1/lab1.ino{cpp}

<<< @/snippets/exp5/lab1/asm.S{asm}

::: tip Hints
- Every TODO is one `sbi` or `cbi` line on port A. Use `DDRA` to make a pin an output and `PORTA` to turn it on or off.
- **TODO 1:** `sbi DDRA, 1`
- **TODO 3:** look at the two lines under `cpi`: they do the opposite.
:::

### Lab work 2: a button picks the LED

While the button is released, LED A is on and LED B is off. While it is held, LED B is on and LED A is off.

Wire LED A to pin 25 (`PA3`), LED B to pin 27 (`PA5`), each through 220 Ω to GND, and the button between pin 23 (`PA1`) and GND.

<<< @/snippets/exp5/lab2/lab2.ino{cpp}

<<< @/snippets/exp5/lab2/asm.S{asm}

::: tip Hints
- **TODO 1:** an input pin's pull-up is turned on by setting its `PORTA` bit, as in [Example 2](#example-2-led-follows-a-button).
- **TODO 2 and 3:** two lines each, one `sbi` and one `cbi`. LED A is bit 3 and LED B is bit 5.
- Both LEDs on at once means a `cbi` is missing.
:::

## Common problems

| Symptom | Cause and fix |
| --- | --- |
| "undefined reference to `start`" | The tab is named `asm.s` instead of `asm.S`, the function has no `.global` line, or the `.ino` lacks `extern "C"`. |
| "token ";" is not valid in preprocessor expressions" | A `;` comment on a `#define` or `#include` line. Those lines go through the C preprocessor; put the comment on its own line. |
| "operand out of range" on an `sbi`, `cbi` or `sbis` line | `#define __SFR_OFFSET 0` is missing, so `PORTB` means its data address, `0x25`. Or the pin is on ports H–L, which these instructions cannot reach. |
| "register number above 15 required" | `ldi` or `cpi` used with `r0`–`r15`. Use `r16`–`r31`, preferably `r18`–`r25`. |
| The board freezes or resets after your function | A missing `ret`, so the processor runs on into whatever follows. Or `r1`, or one of `r2`–`r17`, was changed without being saved. |
| The LED never lights | Its `DDRx` bit is still 0, so the pin is an input and the `PORTx` bit only switches the pull-up. |
| The button always reads pressed, or flickers | The pull-up is not on: set the pin's `PORTx` bit while it is an input. |

## Things to try

- Toggle the LED with one instruction: writing a 1 to a `PINx` bit flips that output, so `sbi PINB, 7` replaces the `cpi`/`breq` logic. Make `led()` a `toggle()` with no argument.
- Return a value: write `byte readButton()` in assembly that puts 1 or 0 in `r24` before `ret`, and print it from `loop()` with `Serial.println()`.
- Wire 8 LEDs to pins 22–29 and write `void show(byte pattern)` that does `out PORTA, r24`. Then count in binary from `loop()`.
- Replace `delay()` with an assembly delay: nested loops of `dec` and `brne`. At 16 MHz, how many passes make 1 ms?
