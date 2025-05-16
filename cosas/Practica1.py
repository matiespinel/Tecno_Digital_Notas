import math 
print("bla bla laa")
a = 4 + 3
print (a)
b = 25.0 / 5.0
print (b)
c= 3.0 <= 3.0000000000000001
d = 3.0 < 3.0000000000000001
print (c, d )
e = 2.0 + 1.0
print (e)

#eje 2
a1 : int = 4
b1 : int = a1 // 3 # va a dar 1
c1 : float = a1 / 3 # va a dar 1.3 hasta repetir 3 16 vecesz
s1 : str = 'dificil ' #string dificil 
print (b1, c1)
f = a1 + 1 // 3 # va a dar 4
g = (a1 + 1) // 3 # va a dar 1
h =  5 * a1 // 3 + 1 # va a dar 7
i = 5 * b1 + 1 # va a dar 6
j = 5 * a1 / 3 + 1 #va dadr 7.6 periodico 16 veces
k = 5 * " hola" #5 veces lapalabra hola
l = 2 * ("uh-" + "la-" +"’la" + "! ") # la frase 2 veces reptida 
m = str(42) + " es el colectivo." # 42 es el bondi
n = str(2 ** 10) == str(6 * a1 + 1000000 // (10 ** 3)) #1024, 1024 // 24 + 1000 true 
o = 40 <= len(s1) * 13 + int(c1) # true
p = s1[5] in "Esta frase" + " no posee esa vocal." #/ false
print (math.pi)
q = str(math.pi - float(b1)) #va a dar 2, todos los decimales de pi 
print (f, g, h, i, j, k, l, m, n, o, p, q)
#eje 3 
a : str = '10 '
print (a ) # 10

b : str = a + '5' # 105
print (a , b) # 10105

b = b + '1' # 1051
print (a , b) # 101051

