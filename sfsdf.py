def simBP(n, m):
    bin_n = bin(n)[2:]
    bin_m = bin(m)[2:]
    count = 0
    for i in range(min(len(bin_n), len(bin_m))):
        if bin_n[i] == bin_m[i]:
            count += 1
        else:
            break
    return count

total = 0
for i in range(20, 92):
    if simBP(i, 1000) == 3:
        print(f"{i}: {bin(i)[2:]}")
        total += 1

print("Total:", total)
