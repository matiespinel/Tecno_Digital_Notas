def simbp_con_lista(n: int, xs : list[int]) -> list[int]:
    """ Requiere : n > 0
        Devuelve: una lista que contiene el resultado de realizar una similitud binaria del prefijo(definida como
        la longitud del prefijo común más largo entre las representaciones
        binarias de n y m.) entre n y todos los elementos de xs
    """
    #se puede hacer con for o while?
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
        Inv: conta representa la cantidad de dígitos consecutivos iguales entre las representaciones binarias de 
        n y m, hasta la posición actual i."
        Demostración de fin de ciclo:
- Al entrar a la función se declaran las siguientes variables: bin_n, bin_m(representaciones binarias de los int n y m respectivamente, distintos de 0), i : int = 0 y terminacion : bool = true
- la condición del ciclo es que i sea menor a la longitud tanto de bin_n como de bin_m y que terminacion == True
- Una vez se entra al ciclo nos encontramos con un if, que prueba que el [i] dígito de n y m sean iguales, si lo son se suma 1 al contador pero si no lo son se modifica terminacion para que sea flase, termiando ahi el ciclo
- En el caso de que el if devuelve true se suma 1 a contador ya que ambos numeros coinciden en ese digito binario y tambien se suma 1 a i modificando su valor (bin_n y bin_m no son modificados)
- al sumar 1 a i nos aseguramos que en algún punto i va a, o ser mayor a la longitud de bin_n y m o los dígitos bin_m[i] y bin_n[i] no van a coincidir lo que haría que termine el ciclo y por consiguiente la función. 

        1. Sabemos que el ciclo termina por lo demostrado en el apartado de terminación. 
        Cuando el ciclo finaliza, i equivale a la longitud del número binario más corto.
        2. Según el invariante, hasta ese punto conta representa la cantidad de dígitos consecutivos 
        iguales entre las representaciones binarias de n y m, hasta la longitud del número binario más corto.
        3. Cuando hablamos de dígitos consecutivos iguales que como máximo llegan hasta 
        dicha longitud, nos referimos al prefijo común más largo de los números binarios.
        4. Por lo tanto, podemos afirmar que al finalizar el ciclo, conta equivale a l
        a longitud del prefijo común más largo entre las representaciones binarias de
        n y m, que es justamente lo que se busca.
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



nums = [-21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40]
for x in nums:
    print(simBP(2, x))

print (simBP(2**30, 2**31))