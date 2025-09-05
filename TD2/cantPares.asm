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

; Ejemplo:
;Supongamos un array de 4 numeros, {0,1,2,3,}
;Primero se compara una constante a 0 con la cantidad de numeros(0=!4)
;se carga en R3 el primer valor del array (0)
;se realiza una AND con una constante de 1 (0 AND 1 = 0)
;esto va a dar flag de 0, por ende salta a par 
;dentro de par se le suma 1 al contador(R4), se avanza el puntero y se le resta 1 al contador de numeros del array(R1)
;se salta dentro del loop y se cargqa devuelta otro numero en R3 (1)
;se realiza una AND con una constante de 1 (1 AND 1 = 1)
;esto va a dar flag de 1, por ende salta a impar
;simplemente avanza el puntero, resta 1 al contador de numeros del array(R1)
;y esto se repite hasta que la cantidad de numeros dentro de larray sea 0
;una vez sea 0 se va a la etiqueta de rest, se realiza un POP de todos los registros menos R4 para devolverlos a su valor original
;y finalmente pasa a un loop infinito de halt.