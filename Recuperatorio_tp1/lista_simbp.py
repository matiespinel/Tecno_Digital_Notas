def simbp_con_lista(n: int, xs : list[int]) -> list[int]:
    """ Requiere : n > 0
        Devuelve: una lista que contiene el resultado de realizar una similitud binaria del prefijo(definida como
        la longitud del prefijo común más largo entre las representaciones
        binarias de n y m.) entre n y todos los elementos de xs
    """
    res: list[str] = []
    i : int = 0
    while i < len(xs):
        res.append(simBP(n, xs[i]))
        i = i + 1

    return res 

def simBP(n:int, m:int) -> int:
    ''' Requiere: n>0, m>0
        Devuelve: la similitud binaria de prefijo entre n y m, definida como
        la longitud del prefijo común más largo entre las representaciones
        binarias de n y m. 
        '''
    bin_n : str  = bin(n).replace('0b','')
    bin_m : str = bin(m).replace('0b','')
    i : int = 0
    conta : int = 0
    terminacion: bool = True
    while terminacion and i < len(bin_n) and i < len(bin_m):
        if bin_n[i] == bin_m[i]:
            conta = conta + 1
            i = i + 1
        else:
            terminacion = False
    return conta
