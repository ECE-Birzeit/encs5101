; example2.s: read two constants, compute (a + b - 1) * 4, store it in RAM

        PRESERVE8
        THUMB

        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x20001000          ; initial stack pointer
        DCD     Reset_Handler       ; reset vector
        ALIGN

        AREA    MYRAM, DATA, READWRITE
SUM     DCD     0                   ; one word of RAM, at 0x20000000

        AREA    MYCODE, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler
Reset_Handler
        LDR     R1, NUM1            ; R1 = value stored at NUM1
        LDR     R2, NUM2            ; R2 = value stored at NUM2

        ADD     R0, R1, R2
        SUBS    R0, R0, #1
        LSLS    R3, R0, #2          ; shift left by 2 = multiply by 4

        LDR     R4, =SUM            ; R4 = address of SUM
        STR     R3, [R4]            ; SUM = R3
        LDR     R6, [R4]            ; read it back to check

STOP    B       STOP

; Constants live in flash, after the code
NUM1    DCD     5
NUM2    DCD     7

        END
