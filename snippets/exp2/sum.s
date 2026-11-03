; sum.s: SUM = N + (N-1) + ... + 1

        PRESERVE8
        THUMB

        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x20001000          ; initial stack pointer
        DCD     Reset_Handler       ; reset vector
        ALIGN

        AREA    MYRAM, DATA, READWRITE
SUM     DCD     0

        AREA    MYCODE, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler
Reset_Handler
        LDR     R1, N               ; R1 = loop counter, starts at N
        MOV     R0, #0              ; R0 = running total

LOOP    ADD     R0, R0, R1          ; total += counter
        SUBS    R1, R1, #1          ; counter--, and set the flags
        BGT     LOOP                ; repeat while counter > 0

        LDR     R3, =SUM
        STR     R0, [R3]            ; SUM = total

STOP    B       STOP

N       DCD     5

        END
