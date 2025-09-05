SET R7, 0xFF        ; pila

PUSH |R7|, R0   ; salvar puntero
PUSH |R7|, R1   ; salvar size
PUSH |R7|, R2
PUSH |R7|, R3
PUSH |R7|, R6

SET R4, 0x00    ; contador = 0
SET R2, 0x01    ; constante 1
SET R6, 0x00    ; constante 0

loop:
    CMP R1, R6      ; size == 0
    JZ rest           

    LOAD R3, [R0]    ; R3 = *p
    AND R3, R2
    JZ par              

impar:
    ADD R0, R2      ; avanzar puntero
    SUB R1, R2          
    JMP loop

par:
    ADD R4, R2          
    ADD R0, R2     ; avanzar puntero
    SUB R1, R2          
    JMP loop

rest:
    POP |R7|, R3
    POP |R7|, R2
    POP |R7|, R1
    POP |R7|, R0
    POP |R7|, R6

halt:
    JMP halt
