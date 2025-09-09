start:
    SET R7, 0xff   ; Puntero de pila
    SET R0, 0x1c     ; Valor a apilar
    PUSH |R7|, R0    ; Pila = {0x1c}, R7 = 0xfe
    STRPOP |R7|, 0xe0 ; Saca de la pila y lo guarda en Mem[0xe0]
halt:
    JMP halt