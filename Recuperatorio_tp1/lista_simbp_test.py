
import unittest

# Se importa el codigo a testear.
from lista_simbp import simbp_con_lista, simBP

class TestListSimBP(unittest.TestCase):

    def test_vacio(self):
        self.assertEqual(simbp_con_lista(1, []),[] )
        self.assertEqual(simbp_con_lista(2, []),[] )
        self.assertEqual(simbp_con_lista(3, []),[] )
        #se pasa la funcion que querramos, los valores de entrada y despues la salida esperada.
    def test_muchos_numeros(self):
        self.assertEqual(simbp_con_lista(int(2), [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]),[1,2,1,2,2,1,1,2,2,2,2,1,1,1,2,2,2,2,2])
    def test_prefijos(self):
        #que el binario de n este dentro de la representaacion bianria de los numeros de la lista
        pass
    def test_todos_cero(self):
        pass
    
    
    def test_simBP_mismo_numero(self):
        # Ambos argumentos coinciden.
        self.assertEqual(simBP(1, 1), 1)  # 1
        self.assertEqual(simBP(5, 5), 3)  # 101
        self.assertEqual(simBP(9, 9), 4)  # 1001
        self.assertEqual(simBP(256, 256), 9)  # 100000000

    def test_simBP_n_menor_m(self):
        # El primer argumento es menor que el segundo
        self.assertEqual(simBP(1, 2), 1)  # 1     10
        self.assertEqual(simBP(1, 4), 1)  # 1    100
        self.assertEqual(simBP(3, 4), 1)  # 11   100
        self.assertEqual(simBP(3, 7), 2)  # 11   111
        self.assertEqual(simBP(4, 8), 3)  # 100  1000
        self.assertEqual(simBP(5, 15), 1) # 101  1111

    def test_simBP_n_mayor_m(self):
        # El primer argumento es mayor que el segundo
        self.assertEqual(simBP(2, 1), 1)  # 1     10
        self.assertEqual(simBP(4, 1), 1)  # 1    100
        self.assertEqual(simBP(4, 3), 1)  # 11   100
        self.assertEqual(simBP(7, 3), 2)  # 11   111
        self.assertEqual(simBP(8, 4), 3)  # 100  1000
        self.assertEqual(simBP(15, 5), 1) # 101  1111

    def test_simBP_prefijos(self):
        # La representación binaria de un número es prefijo de la del otro.
        self.assertEqual(simBP(5, 10), 3)  # 101  1010
        self.assertEqual(simBP(10, 5), 3)  # 101  1010
        self.assertEqual(simBP(45, 22), 5) # 10110 101101
        self.assertEqual(simBP(22, 45), 5) # 101101 10110
        self.assertEqual(simBP(7, 14),3) # 111 1110
        self.assertEqual(simBP(14, 7),3) # 1110 111

    def test_simBPN_numeros_grandes(self):
        # ** es el operador para calcular potencias (a**b es a elevado a la b).
        self.assertEqual(simBP(2**30, 2**30), 31)      # 100...00  100...00
        self.assertEqual(simBP(2**30, 2**30 - 1), 1)   # 100...00   11...11
        self.assertEqual(simBP(2**30, 2**30 + 1), 30)  # 100...00  100...01
        self.assertEqual(simBP(2**30-1, 2**30-1), 30)  #  11...11   11...11


unittest.main()
#  Desarrolo en base 2 de algunos números enteros
#  1 1
#  2 10
#  3 11
#  4 100
#  5 101
#  6 110
#  7 111
#  8 1000
#  9 1001
# 10 1010
# 11 1011
# 12 1100
# 13 1101
# 14 1110
# 15 1111
# 16 10000
# 17 10001
# 18 10010
# 19 10011
# 20 10100
# 21 10101
# 22 10110
# 23 10111
# 24 11000
# 25 11001
# 26 11010
# 27 11011
# 28 11100
# 29 11101
# 30 11110
# 31 11111
# 32 100000
