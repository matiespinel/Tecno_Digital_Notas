#una funcion es un programa dentro de otro, que nos permite abtraer funcionalidades. 
def pas ():
    pass 
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
