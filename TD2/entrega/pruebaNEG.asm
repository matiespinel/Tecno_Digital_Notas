start:
    SET R0, 0x1c     ; Valor binario = 00011100
    NEGHIGHNIBBLE R0; sale: 00010011= 13
halt:
    JMP halt