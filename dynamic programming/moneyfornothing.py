x = map(int, input())
pros = [0] * int(x[0])
cons = [0] * int(x[1])


for i in range(len(pros)):
    a, b = input().split()
    pros[i][0] = int(a)
    pros[i][1] = int(b)

for i in range(len(cons)):
    a, b = input().split()
    cons[i][0] = int(a)
    cons[i][1] = int(b)


maxx = 0

print(cons[1])

for i in pros:
    for j in cons:  
        ran = j[1] - i[1] 
        prof = j[0] - i[0]
        if (ran*prof) > maxx:
            maxx = ran*prof


map(int, split())