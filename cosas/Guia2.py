#1
#a, la parte a no tiene returns
#b, tiene return, la funcion hace 
#c, fun 1 suma 1, la otra le suma 1 tmb pero llama primero a la otra por ende suma 2
#d, fuca bien, tma un numero lo multip por 2 y le suma el otro q metas.
def f2c (f : float) -> float:
    res : float   = (f - 32) * 5 / 9
    print (res)
    return res

f2c (70)
def factorial (n : int) -> int:
    copia = n
    while copia > 1:
        n = n * (copia -1)
        copia = copia -1
    return n    
print (factorial (5))
def inverso(x: float) -> float:
  ''' Requiere: x!=0
      Devuelve: el resultado de dividir 1 por x. 
  '''
  return 1/x
#si quers el inverso tenes que dividir x por -1 aca se divido por x y el devuelv ees incorrecto.

def cuadrado(n: int) -> int:
  '''Requiere: Nada.
      Devuelve: el resutlado de elevar n al cuadrado.
  '''
  return n**n
#la funcion requiere un n ahi hay un error y aparte se escribe con un solo * si se quere levar al cuadrado, hacer ** eleva n a n veces, si se quere mantener el ** cambiar el n por un 2
n:int = 3
print("El cuadrado de", n, "es", cuardado(n))

n:int = "hola"
print("El cuadrado de", n, "es", cuadrado(n)) #necesito un int, el string hola no lo es
x:float = 2.0
print("El inverso de", x, "es", inverso(x)) #parentesis de mas 

x:float = 0,0 #eso era una o 
print("El inverso de", x, "es", inverso(X)) #no poder poner un 0 

