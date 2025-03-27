
import math 
print(math.log(math.e))
print(1/3)
print(len('3333333333333333'))
x:float = 47564273 #esto es un type hint, le da al lector del codigo una pista de que tipo es sin tener qe determinarla. 
print(x)
print(type(x))

mi: float = 50.0
def km (mi) -> float:
    if mi < 0:
        print("no se pueden distancia negativa")
        return 
    else:
        km : float = mi * 1.60934
        mensaje : str = str(int(mi)) + " millas son " + str(int(km)) + " kilometros"
        print (mensaje)
        return
km (mi)
def f (x, y):
    x = 10
    return x + y
b = 8
r = f(b, b)
print(r)
r = f(x, b) #va a dar error pq no esta definida
print(r)

def dist (a: float,a2 : float,b : float,b2 : float ) -> float:
    distaciaX = a2 - a  #requiere nada, devuelve la dsitancia en un float
    distaciaY = b2 - b
    return math.sqrt(distaciaX**2 + distaciaY**2)
def cicular(a : str, b: str):
    return a in (b + b) #requiere que len(a) = len(b)