f = open("sds", "w")
i = 0
while i <= 1000:
    f.write(str(i) + "\n")
    i = i + 1

def sumdig(num) -> int:
    num = int(num)
    i = 0
    res = 0
    while i <=num - 1:
        res = num[i] + num[i+1]
        i = i + 1
    return res
    
    
    
    
    
for linea in f:
    if sumdig(linea) == 15:
        print(linea)