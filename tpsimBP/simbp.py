def simBP(n:int, m:int) -> int:
    ''' Requiere: n>0, m>0
        Devuelve: la similitud binaria de prefijo entre n y m, definida como
        la longitud del prefijo común más largo entre las representaciones
        binarias de n y m. '''
    bin_A : int  = bin(n).replace('0b','')
    bin_B : int = bin(m).replace('0b','')
    i : int = 0
    conta : int = 0
    while i < len(bin_A) and i < len(bin_B):
        if bin_A[i] == bin_B[i]:
            conta = conta + 1
            i = i + 1
        else: return conta      
    return conta
    

def cantidad_con_simBP_en_intervalo(n : int, a : int, b : int, k : int) -> int:
    ''' Requiere: n>0, a>0, b>0, k>0, a<=b
        Devuelve: la cantidad de números entre a y b (inclusive)
        cuya simBP con n es k.'''
    i : int= min(a, b)
    res : int = 0
    while (i <= max(a, b)):
        if simBP(i, n) == k:
            res = res + 1
        i = i + 1
    return res

def existe_con_simBP_en_intervalo(n : int, a : int, b : int, k : int) -> bool:
    ''' Requiere: n>0, a>0, b>0, k>0, a<=b
        Devuelve: True si existe algún número entre a y b (inclusive)
        cuya simBP con n es k; False en caso contrario.'''
    return cantidad_con_simBP_en_intervalo(n, a, b, k) > 0

def numero_con_mayor_simBP_en_intervalo(n : int, a: int, b: int) -> int:
    ''' 
    Requiere: n > 0, a > 0, b > 0, a <= b
    Devuelve: el número entre a y b (inclusive) con mayor simBP con n.
              En caso de haber más de uno, devuelve el menor de ellos.
    '''
    numBin : int = 0
    numList : int = 0
    i : int = min(a, b)
    resSIMBP : int = 0
    while i <= max(a, b):
        resSIMBP = simBP(i, n)
        if resSIMBP > numBin:
            numBin = resSIMBP
            numList = i
        elif resSIMBP == numBin:
            if i < numList:
                numList = i
                
        i += 1
    return numList
    

print (cantidad_con_simBP_en_intervalo(91, 20, 1000, 3))
print (numero_con_mayor_simBP_en_intervalo(10, 21, 29))