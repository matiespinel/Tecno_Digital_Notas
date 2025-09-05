modArray:
    SET R7, 0xFF
    PUSH |R7|, R0
    PUSH |R7|, R1
    PUSH |R7|, R2
    PUSH |R7|, R3
    PUSH |R7|, R5
    PUSH |R7|, R6

    SET R2, 0x01        ; constante 1
    SET R5, 0x00        ; constante 0
    SET R6, 0x03        ; constante 3 

loop:
    CMP R1, R5          ; size == 0
    JZ fin

    LOAD R3, [R0]       ; R3 = *p

    AND R3, R6          ; R3 AND 3 (11)
    JZ mult4
    CMP R3, R5
    JZ mult            
;resto
    MOV R4, R3          ; copia valor original a R4
    SHL R3, R2           ; ×4
	SHL R3, R2
    ADD R3, R4          ; + original → ×5
	SUB R3, R2          ; -1
   	STR [R0], R3        ; guardar en memoria
   	ADD R0, R2
   	SUB R1, R2
   	JMP loop

mult:
   	SHR R3, R2           ; /4
	SHR R3, R2
   	SUB R3, R2          ; -1
   	STR [R0], R3        ; guardar en memoria
   	ADD R0, R2
   	SUB R1, R2
   	JMP loop

fin:
    POP |R7|, R6
	POP |R7|, R5
    POP |R7|, R3
	POP |R7|, R2
    POP |R7|, R1
 	POP |R7|, R0

halt:
    JMP halt

