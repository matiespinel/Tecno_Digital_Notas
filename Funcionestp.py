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
        