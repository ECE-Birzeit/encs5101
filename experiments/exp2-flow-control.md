---
title: Flow Control Instructions
description: Compare instructions, condition codes, branches and loops on the Cortex-M4, and walking byte strings and word arrays in memory.
short: "Flow Control"
---

# Flow Control Instructions

So far every program has run straight from top to bottom. In this lab you make decisions and loops: compare two values, branch on the result, and walk through a string or an array in memory.

## Objectives

- Set the flags with `CMP` and branch on them with the condition codes.
- Write `if`/`else` and loops in assembly.
- Store strings and arrays with `DCB`/`DCD` and step through them with a pointer.

## Background

### Comparing

A compare does a subtraction (or addition, or logic operation) only to set `N Z C V`. The result itself is thrown away. See [Experiment 1](./exp1-arm-basics#core-registers) for what each flag means.

| Instruction | Sets the flags from | Typical use |
| --- | --- | --- |
| `CMP Rn, Rm` / `CMP Rn, #imm` | `Rn − Rm` | Is `Rn` equal to, less than or greater than `Rm`? |
| `CMN Rn, #imm` | `Rn + imm` | Compare with a negative constant: `CMN R0, #5` tests `R0` against −5 |
| `TST Rn, #mask` | `Rn AND mask` | Is any bit of `mask` set in `Rn`? |
| `TEQ Rn, Rm` | `Rn XOR Rm` | Are the two exactly equal? |

Any data-processing instruction ending in **S** (`SUBS`, `ADDS`, `ANDS` …) sets the flags too, which often saves a separate `CMP`.

### Condition codes

Append a condition to `B` to branch only when it holds. Pick the signed or unsigned version according to how **you** interpret the numbers. The CPU does not know.

| Suffix | Meaning after `CMP a, b` | Flags tested |
| :-: | --- | --- |
| `EQ` / `NE` | a = b / a ≠ b | `Z = 1` / `Z = 0` |
| `GT` / `GE` | a > b / a ≥ b, **signed** | `Z = 0 and N = V` / `N = V` |
| `LT` / `LE` | a < b / a ≤ b, **signed** | `N ≠ V` / `Z = 1 or N ≠ V` |
| `HI` / `HS` | a > b / a ≥ b, **unsigned** | `C = 1 and Z = 0` / `C = 1` |
| `LO` / `LS` | a < b / a ≤ b, **unsigned** | `C = 0` / `C = 0 or Z = 1` |
| `MI` / `PL` | result negative / zero or positive | `N = 1` / `N = 0` |
| `VS` / `VC` | overflow / no overflow | `V = 1` / `V = 0` |

`HS` and `LO` are also written `CS` and `CC` (carry set, carry clear).

### Branches

| Instruction | Effect |
| --- | --- |
| `B label` | Always jump to `label` |
| `Bcc label` | Jump only if condition `cc` holds, e.g. `BEQ`, `BLT`, `BHI` |
| `CBZ Rn, label` / `CBNZ Rn, label` | Jump if `Rn` is zero / not zero. No `CMP` needed and the flags are untouched, but only **forward** and only with `R0`–`R7`. |
| `BL label` | Call a subroutine: jump, and save the return address in `LR` |
| `BX LR` | Return from a subroutine |

### Common patterns

```asm
; if (R0 == 10) R1 = 1; else R1 = 2;
        CMP     R0, #10
        BNE     notTen
        MOV     R1, #1
        B       done
notTen  MOV     R1, #2
done

; for (i = 10; i > 0; i--) { ... }
        MOV     R4, #10
loop    ; ... loop body ...
        SUBS    R4, R4, #1          ; the S sets Z when R4 reaches 0
        BNE     loop
```

### Conditional execution with `IT`

On the Cortex-M, a condition on anything other than a branch needs an **IT** (If-Then) instruction first. `IT` takes up to three more `T` (then) or `E` (else) letters, one per following instruction.

```asm
; R2 = max(R0, R1), with no branch
        CMP     R0, R1
        ITE     GT                  ; next: Then if GT, Else
        MOVGT   R2, R0
        MOVLE   R2, R1
```

::: details Reading the department manual?
The manual describes the **ARM-state** encoding: a 4-bit condition field in every instruction and a 24-bit branch offset added to PC + 8. Classic ARM cores work that way, but a Cortex-M runs only **Thumb** code, which encodes branches differently and uses `IT` for everything else. You do not need either encoding for this lab.
:::

### Strings and arrays in memory

```asm
msg     DCB     "Hi!", 0            ; 4 bytes: 'H' 'i' '!' 0
vec     DCD     12, -3, 54          ; 3 words, 4 bytes each
```

A string is a sequence of bytes, and the terminating `0` is how a program knows where it ends. Walk it with a pointer register and `LDRB`. An array of `DCD` words is walked with `LDR`, and the pointer moves by **4** for each element.

| Instruction | Effect |
| --- | --- |
| `LDRB R2, [R0]` | `R2` = the byte at `R0` |
| `LDRB R2, [R0], #1` | `R2` = the byte at `R0`, **then** `R0 = R0 + 1` (post-indexed) |
| `LDR R3, [R1], #4` | `R3` = the word at `R1`, then `R1 = R1 + 4` |
| `CMP R2, #'a'` | Compare with a character's ASCII code |

## Examples

Create a project for each, as in [Experiment 1](./exp1-arm-basics#examples), and step through it.

### Example 1: string length

<<< @/snippets/exp2/strlen.s{asm}

`R1` ends at 12. To see the string itself, open **Memory 1** at the address `R0` holds after the first `LDR`, and switch the view to ASCII.

Try replacing the `LDRB` and the first `ADD` with a single post-indexed `LDRB R2, [R0], #1`.

### Example 2: sum of 1 to N

<<< @/snippets/exp2/sum.s{asm}

`R0` ends at 15 (5 + 4 + 3 + 2 + 1). `SUBS` sets the flags that `BGT` tests, so the loop needs no `CMP`. Change `SUBS` to `SUB` and see what happens.

## Lab work

### Lab work 1: counting vowels

Write `CountVowelsOne.s` to count the vowels and the non-vowels in this string:

```asm
string1 DCB     "ARM assembly language is important to learn!", 0
```

- `R0`: address of the current character.
- `R1`: number of vowels.
- `R2`: number of non-vowels: every other character before the `0`, including spaces and punctuation.

::: tip Hints
- Load each character into a spare register such as `R3`, since `R1` and `R2` are taken.
- The string has an uppercase `A`. `ORR R3, R3, #0x20` turns an uppercase letter into lowercase, so you only compare against `a e i o u`.
- Five `CMP`/`BEQ` pairs that all branch to the same "is a vowel" label are enough.
:::

### Lab work 2: values above the average

Write a program that counts how many values in this 10-element vector are greater than the vector's average:

```asm
vec     DCD     12, -3, 54, 81, 23, -15, 0, 40, -73, 66
```

- `R1`: address of the vector.
- `R0`: the average.
- `R2`: number of values greater than the average.

::: tip Hints
- You need two passes: one to sum the values and compute the average, one to count.
- The values are **signed**. Choose the division and the branch condition to match.
- Reset `R1` to the start of the vector before the second pass.
:::

## Common problems

| Symptom | Cause and fix |
| --- | --- |
| The loop never ends, or runs once | The instruction before the branch does not set the flags. Use `SUBS`, not `SUB`, or add a `CMP`. |
| Negative values are treated as huge numbers | You used an unsigned condition (`HI`, `LO`) on signed data. Use `GT`, `LT`, `GE` or `LE`. |
| The count is too high and the pointer runs past the data | The string has no terminating `, 0`, or the word pointer moves by 1 instead of 4. |
| `MOVGT` or another conditional instruction is rejected | It needs an `IT` instruction right before it. |
| `CBZ` gives a branch range error | `CBZ` only jumps forward, a short distance. Use `CMP` and `BEQ` instead. |
| A vowel count of 0 | You compared against `'a'` but loaded with `LDR` instead of `LDRB`, so the register holds four characters at once. |
