import unittest
from funzzzzzziones import km
def ultimo_caracter(s:str) -> str: #sacar guion
    ''' Requiere:  len(s)>0
        Devuelve: el ultimo caracter de s.
    '''
    vr:int = s[len(s)-1] #reste pq sino fuera de rango
   
    return vr

texto:str = "hola mundo"
ult:str = ultimo_caracter(texto)
print(ult)
def cont(texto:str) :
    vocales = "aeiouAEIOU"
    contador = sum(1 for letra in texto if letra in vocales)
    return contador
print(cont(texto))
class Testkm(unittest.TestCase):
    def test_xx(self):
        self.assertEqual(km(30), 10) #para float usar assertAlmostEqual
unittest.main()