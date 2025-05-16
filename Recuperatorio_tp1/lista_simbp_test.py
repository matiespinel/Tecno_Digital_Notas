
import unittest

# Se importa el codigo a testear.
from lista_simbp import simbp_con_lista, simBP

class TestListSimBP(unittest.TestCase):

    def test_vacio(self):
        #que funcione con listas vacias
        self.assertEqual(simbp_con_lista(1, []),[] )
        self.assertEqual(simbp_con_lista(2, []),[] )
        self.assertEqual(simbp_con_lista(3, []),[] )
        
    def test_muchos_numeros(self):
        #que funcione con listas largas 
        self.assertEqual(simbp_con_lista(2, [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]),[1,2,1,2,2,1,1,2,2,2,2,1,1,1,1,2,2,2,2,2])
        self.assertEqual(simbp_con_lista(2, [21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40]),[2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2])
    def test_prefijos(self):
        #que el binario de n este dentro de la representaacion bianria de los numeros de la lista
        self.assertEqual(simbp_con_lista(7,[14, 59, 63, 122, 127, 990]), [3,3,3,3,3,3]) # 1110 # 111011 # 111111 # 1111010 # 1111111 # 1111011110
        self.assertEqual(simbp_con_lista(9, [144, 145, 146, 147, 148, 149]), [4, 4, 4, 4, 4, 4]) #10010000 # 10010001 #10010010 #10010011 #10010100 #10010101
        self.assertEqual(simbp_con_lista(6, [96, 97, 98, 99, 100, 101]), [3, 3, 3, 3, 3, 3]) # 1100000 #1100001 # 1100010 # 1100011 # 1100100 # 1100101
        self.assertEqual(simbp_con_lista(10, [160, 161, 162, 163, 164, 165]), [4, 4, 4, 4, 4, 4]) # 10100000 # 10100001 # 10100010 # 10100011 # 10100100 # 10100101
    def test_muy_grandes(self):
        self.assertEqual(simbp_con_lista(2**30, [2**30, 2**31, 2**32, 2**33, 2**34, 2**35, 2**36, 2**30-1]),[31,31,31,31,31,31,31,1])
        self.assertEqual(simbp_con_lista(2**20, [2**20, 2**21, 2**22, 2**23, 2**24, 2**25]),[21, 21, 21, 21, 21, 21])
    def test_aleatorios(self):
        #dado un n cualquiera y una lista de numeros aleatorios desordenados
        self.assertEqual(simbp_con_lista(13, [3, 13, 26, 7, 20, 255]),[2, 4, 4, 2, 1, 2]) 
        self.assertEqual(simbp_con_lista(4, [0, 1, 2, 3, 4, 5]),[0, 1, 2, 1, 3, 2])
        self.assertEqual(simbp_con_lista(19, [19, 18, 17, 255, 3, 7]),[5, 4, 3, 1, 1, 1])
    # bin(19)=10011
    def test_n_mayor(self):
        #el argumento n > al mayor numero dentro de la lista
        self.assertEqual(simbp_con_lista(20, [1, 2, 3, 4]),[1, 2, 1, 2])
        self.assertEqual(simbp_con_lista(100, [50, 60, 70]),[6, 2, 1])
        self.assertEqual(simbp_con_lista(255, [128, 64, 32]),[1, 1, 1])
        self.assertEqual(simbp_con_lista(1023, [512, 511, 1000]),[1, 9, 5])
    

    
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
# 33 100001
# 34 100010
# 35 100011
# 36 100100
# 37 100101
# 38 100110
# 39 100111
# 40 101000