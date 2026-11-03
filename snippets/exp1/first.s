; first.s: the smallest complete program. Copy this skeleton for every lab.

        PRESERVE8
        THUMB

; ---- Vector table: the first two words the CPU reads at reset ----
        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x20001000          ; initial stack pointer
        DCD     Reset_Handler       ; address of the first instruction to run
        ALIGN

; ---- Program ----
        AREA    MYCODE, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler
Reset_Handler
        ; your code starts here
        MOV     R0, #12

STOP    ADD     R0, R0, #4          ; R0 grows by 4 every time round
        B       STOP

        END
