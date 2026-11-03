; MyFirstARM.s: step through and fill in every ?

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
        MOV     R2, #0x01           ; R2 = ?
        MOV     R3, #0x02           ; R3 = ?

        MOV     R5, #0x3210         ; R5 = ?
        MOVT    R5, #0x7654         ; R5 = ?
        MOV32   R6, #0x87654321     ; R6 = ?
        LDR     R7, =0x87654321     ; R7 = ?

        ADD     R1, R2, R3          ; R1 = ?
        MOV32   R3, #0xFFFFFFFF     ; R3 = ?
        ADDS    R1, R2, R3          ; R1 = ?   NZCV = ?
        SUBS    R1, R2, R3          ; R1 = ?   NZCV = ?

        MOV     R4, #0xFFFFFFFF     ; R4 = ?
        ADD     R1, R2, R4          ; R1 = ?   did the flags change?
        ADDS    R1, R2, R4          ; R1 = ?   NZCV = ?

        MOV     R2, #0x00000002     ; R2 = ?
        ADDS    R1, R2, R4          ; R1 = ?   NZCV = ?

        MOV     R2, #0x00000001
        MOV     R3, #0x00000002
        ADDS    R1, R2, R3          ; R1 = ?   NZCV = ?

        MOV     R2, #0x7FFFFFFF
        MOV     R3, #0x7FFFFFFF
        ADDS    R1, R2, R3          ; R1 = ?   NZCV = ?

STOP    B       STOP
        END
