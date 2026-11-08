---
title: ARM Assembly and Keil uVision5
description: The skeleton of an ARM assembly program, the Cortex-M4 registers and flags, and the core data-processing and load/store instructions, run in the Keil simulator.
short: "ARM Assembly and Keil"
---

# ARM Assembly and Keil uVision5

In this lab you write your first ARM assembly programs for an **ARM Cortex-M4** and run them in the Keil simulator. You learn the skeleton every program needs, then use the debugger to watch registers and flags change one instruction at a time.

## Objectives

- Create, build and debug an assembly project in Keil uVision5.
- Know the Cortex-M4 core registers and what the `N`, `Z`, `C` and `V` flags mean.
- Use the move, arithmetic, logic, shift and load/store instructions.

::: tip Before the lab
Read the [Keil setup guide](/setup/keil). It shows how to create a project and use the debugger, which this page assumes.
:::

## Background

### Anatomy of a program

Every program in Experiments 1 and 2 has the same skeleton. Only the part after `Reset_Handler` changes.

<<< @/snippets/exp1/first.s{asm}

| Line | Meaning |
| --- | --- |
| `PRESERVE8`, `THUMB` | Keep the stack 8-byte aligned and assemble Thumb instructions, the only kind a Cortex-M runs. |
| `AREA RESET, DATA, READONLY` | Start a block of memory named `RESET`. The linker puts it at address 0. |
| `__Vectors` and its two `DCD`s | The **vector table**. At reset the CPU loads the first word into the stack pointer and jumps to the address in the second. |
| `AREA MYCODE, CODE, READONLY` | Start the block that holds your instructions. |
| `ENTRY`, `EXPORT Reset_Handler` | Mark where execution starts, and let the linker see that label. |
| `STOP B STOP` | Branch to itself forever. There is no operating system to return to, so a program must never "fall off" its end. |
| `END` | End of the source file. Anything after it is ignored. |

::: warning Columns matter
A **label** must start in column 1. **Instructions and directives** must be indented by at least one space or a tab. Write `MOV R0, #12` in column 1 and the assembler reads `MOV` as a label and complains about an unknown opcode.
:::

Each instruction line has the form:

```asm
label   OPCODE  destination, operand1, operand2     ; comment
```

### Core registers

![Cortex-M4 core registers](/images/exp1/core-registers.jpg)

- **R0–R12**: general-purpose. Use them freely.
- **R13 (SP)**: the stack pointer. It is loaded from the first word of the vector table.
- **R14 (LR)**: the link register, which holds the return address after a `BL` call ([Experiment 2](./exp2-flow-control)).
- **R15 (PC)**: the program counter, the address of the next instruction.
- **xPSR**: the program status register. Its top four bits are the **condition flags**:

| Flag | Set to 1 when the result… | Read it as |
| :-: | --- | --- |
| **N** | has bit 31 set | negative, if the numbers are signed |
| **Z** | is exactly zero | equal, after a compare |
| **C** | carried out of bit 31 on an add, or did **not** borrow on a subtract | unsigned overflow on an add |
| **V** | has the wrong sign, e.g. two positives added to a negative | signed overflow |

Instructions only update the flags when you append **S**: `ADDS` sets them, `ADD` does not. Compare instructions (`CMP`, [Experiment 2](./exp2-flow-control)) always set them.

::: details Memory map
![Cortex-M memory map](/images/exp1/memory-map.jpg)

In the Keil ARMCM4 simulator, your code and constants live from address `0x00000000` (the code region) and RAM starts at `0x20000000`. The stack pointer `0x20001000` sits 4 KB into RAM, and variables you declare in a `READWRITE` area land at `0x20000000`.
:::

### Instruction quick reference

Keep this open while you work. `Rd` is the destination, `Rn`/`Rm` are source registers, and `#imm` is a constant.

**Move**

| Instruction | Effect |
| --- | --- |
| `MOV Rd, #imm` / `MOV Rd, Rm` | `Rd = imm` / `Rd = Rm` |
| `MVN Rd, #imm` | `Rd = NOT imm` (bitwise inverse) |
| `MOVT Rd, #imm16` | Replace the **top** 16 bits of `Rd`, keep the bottom 16 |
| `MOV32 Rd, #imm32` | Any 32-bit constant (assembles to `MOVW` + `MOVT`) |
| `LDR Rd, =imm32` | Any 32-bit constant or label address, loaded from a nearby constant pool |

**Arithmetic**

| Instruction | Effect |
| --- | --- |
| `ADD Rd, Rn, Rm` | `Rd = Rn + Rm` (the last operand can also be `#imm`) |
| `SUB Rd, Rn, Rm` | `Rd = Rn − Rm` |
| `RSB Rd, Rn, #imm` | `Rd = imm − Rn` (reverse subtract) |
| `MUL Rd, Rn, Rm` | `Rd = Rn × Rm` (low 32 bits) |
| `UMULL RdLo, RdHi, Rn, Rm` | 64-bit unsigned product in `RdHi:RdLo` (`SMULL` for signed) |
| `UDIV Rd, Rn, Rm` / `SDIV Rd, Rn, Rm` | `Rd = Rn ÷ Rm`, unsigned / signed, rounded toward zero |

**Logic and shifts**

| Instruction | Effect |
| --- | --- |
| `AND`, `ORR`, `EOR` `Rd, Rn, Rm` | Bitwise AND, OR, XOR |
| `BIC Rd, Rn, Rm` | `Rd = Rn AND NOT Rm`, clears the bits set in `Rm` |
| `ORN Rd, Rn, Rm` | `Rd = Rn OR NOT Rm` |
| `LSL Rd, Rm, #n` / `LSR Rd, Rm, #n` | Logical shift left / right by `n` bits (×2ⁿ / unsigned ÷2ⁿ) |
| `ASR Rd, Rm, #n` | Arithmetic shift right, keeps the sign (signed ÷2ⁿ) |
| `ROR Rd, Rm, #n` | Rotate right |

**Load and store**: the only instructions that touch memory.

| Instruction | Effect |
| --- | --- |
| `LDR Rd, label` | `Rd` = the word stored at `label` |
| `LDR Rd, =label` | `Rd` = the **address** of `label` |
| `LDR Rd, [Rn]` | `Rd` = the word at the address in `Rn` |
| `LDR Rd, [Rn, #4]` | `Rd` = the word at `Rn + 4` |
| `STR Rd, [Rn]` | Store `Rd` at the address in `Rn` |
| `LDRB` / `STRB` | Same, for a single byte |

**Data directives**

| Directive | Effect |
| --- | --- |
| `name DCD 5, 7, -3` | Reserve 32-bit words with these initial values |
| `name DCB "Hi", 0` | Reserve bytes: a string, here null-terminated |

::: details Why `MOV R0, #0x12345678` does not assemble
An instruction is only 16 or 32 bits wide, so there is no room for an arbitrary 32-bit constant. `MOV` accepts any 16-bit value, or a small set of 32-bit patterns such as `0xFF000000` and `0xFFFFFFFF`. For anything else, use `MOV32` or `LDR Rd, =value`. Check the **Disassembly** window to see what the assembler actually produced.
:::

## Examples

For each example, create a project ([Keil → Create a project](/setup/keil#step-3-create-the-project)), paste the code, build, start debugging and step with <kbd>F11</kbd>. **Predict** each register before you step.

### The first program

Use `first.s` from [Anatomy of a program](#anatomy-of-a-program). Step through it and watch `R0` start at 12 and grow by 4 on every loop.

### Example 1: arithmetic

Compute f(x) = 5x² − 6x + 8 for x = 7.

<<< @/snippets/exp1/example1.s{asm}

When it reaches `STOP`, `R3` should hold 211 (`0xD3`).

### Example 2: memory

Load two constants from flash, compute (a + b − 1) × 4, and store the result in a RAM variable.

<<< @/snippets/exp1/example2.s{asm}

Open **Memory 1** at `0x20000000` and watch `SUM` change when `STR` executes.

Note the two forms of `LDR`. `LDR R1, NUM1` loads the **value** stored at `NUM1`. `LDR R4, =SUM` loads the **address** of `SUM`, which `STR` then writes through.

## Lab work

### Lab work 1: watching the flags

Create `MyFirstARM.s` from the program below. Step through it one instruction at a time. After every line, write down the destination register, and after every instruction ending in **S**, write down `N Z C V`.

<<< @/snippets/exp1/labwork1.s{asm}

Then answer:

1. Why does `MOV R5, #0x3210` followed by `MOVT R5, #0x7654` give the same value as `MOV32`?
2. Look at the **Disassembly** window. What did the assembler turn `MOV R4, #0xFFFFFFFF` into, and why?
3. `ADD R1, R2, R4` and `ADDS R1, R2, R4` give the same `R1`. What is different?
4. Why does `0x7FFFFFFF + 0x7FFFFFFF` set `V` but not `C`?

### Lab work 2: temperature conversion

Write `convertF2CandC2F.s`:

1. Put a Fahrenheit temperature, say 70, in `R0`, and leave its Celsius equivalent in `R1`.
2. Put a Celsius temperature, say 22, in `R2`, and leave its Fahrenheit equivalent in `R3`.

C = 5 × (F − 32) ÷ 9  F = 9 × C ÷ 5 + 32

Build it, fix any errors, and step through it watching the registers.

::: tip Hints
- The division is integer division, so the fraction is lost. Multiply **before** you divide, or the error grows.
- F − 32 is negative below freezing. Which division instruction still gives the right answer then?
:::

## Common problems

| Symptom | Cause and fix |
| --- | --- |
| `error: A1163E: Unknown opcode` | An instruction starts in column 1, so it was read as a label. Indent it. |
| A label is reported as an unknown opcode | The label is indented. Move it to column 1. |
| `Immediate … out of range` on `MOV` | The constant does not fit. Use `MOV32` or `LDR Rd, =value`. |
| Registers fill with garbage after the last instruction | The program has no `STOP B STOP` and ran past its end. |
| `STR` runs but the variable never changes | The variable is in a `READONLY` area (flash). Put it in a `READWRITE` area. |
| Debugging will not start | See the [setup troubleshooting](/setup/keil#troubleshooting). |
