##################################################################
# Para diseñar los casos de test, es útil contar con la representación
# binaria de algunos números enteros. Al final de este archivo se encuentra
# el desarrollo en base 2 de algunos números para usar como referencia.
##################################################################

import unittest

# Se importa el codigo a testear.
from simbp import simBP, cantidad_con_simBP_en_intervalo, \
   existe_con_simBP_en_intervalo, numero_con_mayor_simBP_en_intervalo

class TestSimBP(unittest.TestCase):
    def test_simBP_mismo_numero(self):
        # Ambos argumentos coinciden.
        self.assertEqual(simBP(1, 1), 1)  # 1
        self.assertEqual(simBP(5, 5), 3)  # 101
        self.assertEqual(simBP(8, 8), 4)  # 1000
        self.assertEqual(simBP(255, 255), 8)  # 11111111

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

    def test_simBPN_numeros_grandes(self):
        # Probamos algunos números "grandes".
        # ** es el operador para calcular potencias (a**b es a elevado a la b).
        self.assertEqual(simBP(2**30, 2**30), 31)      # 100...00  100...00
        self.assertEqual(simBP(2**30, 2**30 - 1), 1)   # 100...00   11...11
        self.assertEqual(simBP(2**30, 2**30 + 1), 30)  # 100...00  100...01
        self.assertEqual(simBP(2**30-1, 2**30-1), 30)  #  11...11   11...11

    ##### Abreviamos ccsei = cantidad_con_simBP_en_intervalo

    def test_ccsei_intervalo_1(self):
        # Intervalo de tamaño 1 (a==b).
        self.assertEqual(cantidad_con_simBP_en_intervalo(7, 3, 3, 2), 1)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 8, 8, 2), 0)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 8, 8, 1), 1)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 12, 12, 1), 0)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 12, 12, 2), 1)

    def test_ccsei_intervalo_2(self):
        # Intervalo de posible 2 (a+1==b)
        self.assertEqual(cantidad_con_simBP_en_intervalo(7, 3, 4, 2), 1)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 8, 9, 2), 0)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 11, 12, 1), 1)

    def test_ccsei_sin_ninguno(self):
        # No hay ninguno
        self.assertEqual(cantidad_con_simBP_en_intervalo(1, 20, 1000, 2), 0)    # simBP requerida tiene mas digitos que bin(n)
        self.assertEqual(cantidad_con_simBP_en_intervalo(3, 1, 10, 5), 0)       # simBP requerida tiene mas digitos que bin(n)
        self.assertEqual(cantidad_con_simBP_en_intervalo(15, 1, 14, 4), 0)      # Existen numeros pero no en dicho rango.
        self.assertEqual(cantidad_con_simBP_en_intervalo(1023, 40, 125, 7), 0)  # Existen numeros pero no en dicho rango.
        self.assertEqual(cantidad_con_simBP_en_intervalo(7, 8, 9, 3), 0)        # Existen numeros pero no en dicho rango.

    def test_ccsei_casos_varios(self):
        # Algunos casos variados.
        self.assertEqual(cantidad_con_simBP_en_intervalo(91, 20, 1000, 3), 126) # Ejemplo del enunciado.
        self.assertEqual(cantidad_con_simBP_en_intervalo(10, 20, 25, 3), 2)
        self.assertEqual(cantidad_con_simBP_en_intervalo(11, 20, 25, 3), 2)
        self.assertEqual(cantidad_con_simBP_en_intervalo(20, 20, 25, 5), 1)
        self.assertEqual(cantidad_con_simBP_en_intervalo(25, 20, 25, 5), 1)

    ##### Abreviamos ecsei = existe_con_simBP_en_intervalo

    def test_ecsei_intervalo_1(self):
        # Intervalo de tamaño 1 (a==b).
        self.assertTrue(existe_con_simBP_en_intervalo(7, 3, 3, 2))
        self.assertFalse(existe_con_simBP_en_intervalo(15, 8, 8, 2))
        self.assertTrue(existe_con_simBP_en_intervalo(15, 8, 8, 1))
        self.assertFalse(existe_con_simBP_en_intervalo(15, 12, 12, 1))
        self.assertTrue(existe_con_simBP_en_intervalo(15, 12, 12, 2))

    def test_ecsei_intervalo_2(self):
        # Intervalo de posible 2 (a+1==b)
        self.assertTrue(existe_con_simBP_en_intervalo(7, 3, 4, 2))
        self.assertFalse(existe_con_simBP_en_intervalo(15, 8, 9, 2))
        self.assertTrue(existe_con_simBP_en_intervalo(15, 11, 12, 1))

    def test_ecsei_sin_ninguno(self):
        # No hay ninguno
        self.assertFalse(existe_con_simBP_en_intervalo(1, 20, 1000, 2))    # simBP requerida tiene mas digitos que bin(n)
        self.assertFalse(existe_con_simBP_en_intervalo(3, 1, 10, 5))       # simBP requerida tiene mas digitos que bin(n)
        self.assertFalse(existe_con_simBP_en_intervalo(15, 1, 14, 4))      # Existen numeros pero no en dicho rango.
        self.assertFalse(existe_con_simBP_en_intervalo(1023, 40, 125, 7))  # Existen numeros pero no en dicho rango.
        self.assertFalse(existe_con_simBP_en_intervalo(7, 8, 9, 3))        # Existen numeros pero no en dicho rango.

    def test_ecsei_casos_varios(self):
        # Algunos casos variados.
        self.assertTrue(existe_con_simBP_en_intervalo(91, 20, 1000, 3)) # Ejemplo del enunciado.
        self.assertTrue(existe_con_simBP_en_intervalo(10, 20, 25, 3))
        self.assertTrue(existe_con_simBP_en_intervalo(11, 20, 25, 3))
        self.assertTrue(existe_con_simBP_en_intervalo(20, 20, 25, 5))
        self.assertTrue(existe_con_simBP_en_intervalo(25, 20, 25, 5))

    ##### Abreviamos ncmsei = numero_con_mayor_simBP_en_intervalo

    def test_ncmsei_extremo(self):
        # El mayor es uno de los extremos del intervalo
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(20, 20, 25), 20)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(25, 20, 25), 25)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(63, 126, 200), 126)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(63, 65, 126), 126)

    def test_ncmsei_unico_mayor(self):
        # Hay un único número con simBP mayor en el rango.
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(10, 21, 21), 21)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(10, 21, 29), 21)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(14, 21, 28), 28)

    def test_ncmsei_mas_de_un_mayor(self):
        # Hay más de un número con simBP mayor en el rango, se devuelve el 1ro.
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(10, 20, 29), 20)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(14, 20, 29), 28)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(11, 20, 29), 22)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(6, 20, 29), 24)
        self.assertEqual(numero_con_mayor_simBP_en_intervalo(91, 20, 50), 45)  # Ejemplo del enunciado

unittest.main()

####################################################
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
