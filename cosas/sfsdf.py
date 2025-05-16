f = open("palabras.txt")
texto = f.read()  
def contar (letra, palabra):
    rs = 0
    i = 0
    while i < len(palabra):
        if palabra[i] == letra:
            rs = rs + 1
        i = i +1
    return rs

def cinco(linea):
    return contar("a", linea) == 1 and contar("e", linea) == 1 and contar("i", linea) == 1 and contar("o", linea) == 1 and contar("u", linea) == 1
res = "d"        
for linea in texto.split("\n"):
    linea = linea.strip()
    if cinco(linea):
        res = res + linea + " "
print (res)
            