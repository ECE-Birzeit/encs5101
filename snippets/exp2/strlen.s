; strlen.s: count the characters in a null-terminated string

        PRESERVE8
        THUMB

        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x20001000          ; initial stack pointer
        DCD     Reset_Handler       ; reset vector
        ALIGN

        AREA    MYCODE, CODE, READONLY
        ENTRY
        EXPORT  Reset_Handler
Reset_Handler
        LDR     R0, =string1        ; R0 = address of the first character
        MOV     R1, #0              ; R1 = length so far

loop    LDRB    R2, [R0]            ; R2 = the character R0 points at
        CMP     R2, #0              ; reached the terminating 0?
        BEQ     done
        ADD     R0, R0, #1          ; next character
        ADD     R1, R1, #1          ; count it
        B       loop

done                                ; R1 holds the length
STOP    B       STOP

string1 DCB     "Hello world!", 0

        END
