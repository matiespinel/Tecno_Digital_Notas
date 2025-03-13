import math 
print(math.log(math.e))
print(1/3)
print(len('3333333333333333'))
x:float = 47564273 #esto es un type hint, le da al lector del codigo una pista de que tipo es sin tener qe determinarla. 
print(x)
print(type(x))

mi: float = 50.0
def km (mi):
    km : float = mi * 1.60934
    mensaje : str = str(int(mi)) + " millas son " + str(int(km)) + " kilometros"
    print (mensaje)
    return
km (mi)
