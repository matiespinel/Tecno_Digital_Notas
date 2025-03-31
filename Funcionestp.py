def simBP (a : int, b : int) -> int:
    bin_A = bin(a)[2:]
    bin_B = bin(b)[2:]
    i = 0
    conta = 0
    while i < len(bin_A):
        if bin_A[i] == bin_B[i]:
            conta = conta + 1
            i = i + 1
        else: return conta
        
    return conta
print(simBP(4,4))     
def conjunto_a_k(a : int, b : int, n : int, k : int):
    i = a
    while (i <= b):
        resSIMBP = simBP(i, n)
        res = 0 
        if resSIMBP == k:
            res = res + 1
        i = i + 1
    return res

def existe_simBP(a : int, b : int, n : int, k : int):
    if conjunto_a_k(a, b, n, k) > 0:
        return True
    else:
        return False

def simBP_Menores(a : int, b : int, n : int):
    tienen = []
    i = a
    t = 0
    while (i <= b):
        resSIMBP = simBP(i, n)
        tienen.append(i ,resSIMBP)
        i = i + 1