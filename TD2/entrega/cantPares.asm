main:
	SET R7, 0xFF	;stack
	
	SET R0, p	;p
	SET R1, 0x10	;size
	SET R4, 0x00	
	CALL |R7|, cantPares

halt:
	JMP halt

cantPares:
    PUSH |R7|, R0   ; apilo reg
    PUSH |R7|, R1
    PUSH |R7|, R2
    PUSH |R7|, R3   
    PUSH |R7|, R6

    SET R4, 0x00    ; contador = 0
    SET R2, 0x01    ; constante 1
    SET R6, 0x00    ; constante 0 para comparacion

loop:
    CMP R1, R6      ; size == 0?
    JZ fin          ; Si es cero, terminar.

    LOAD R3, [R0]   ; R3 = *p
    AND R3, R2      ; R3 = R3 & 1 (chequeo de paridad)
    JZ par          ; Si es cero (par), saltar a 'par'

; impar :
    JMP update ; Si es impar, solo actualiza

par:
    ADD R4, R2      ; contador++
        
update:
    ADD R0, R2      ; p++
    SUB R1, R2      ; size--
    JMP loop

fin:
    POP |R7|, R6    ; Restaurar registros 
    POP |R7|, R3
    POP |R7|, R2
    POP |R7|, R1
    POP |R7|, R0

	RET |R7|

p:
    DB 0x01 
    DB 0x02 
    DB 0x04 
    DB 0x08 
    DB 0x03 
    DB 0x03 
    DB 0xA1 
    DB 0xC0 
    DB 0xFF 
    DB 0x40 
    DB 0x55 
    DB 0xCC 
    DB 0xBD 
    DB 0x45 
    DB 0x9A 
    DB 0xEE