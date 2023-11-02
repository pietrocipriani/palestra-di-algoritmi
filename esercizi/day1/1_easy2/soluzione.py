
input = open('input.txt', 'r')
output = open('output.txt', 'w')

N = int(input.readline())

# Inizializziamo il massimo a -1. È il default.
# Inoltre sicuramente -1 è minore di qualsiasi altra soluzione valida. Dato che i termini sono positivi.
massimo = -1

for line in input.readlines():
    a,b = (int(num) for num in line.strip().split(' '))

    sum = a + b
    
    # se la somma è pari
    if sum % 2 == 0:
        massimo = max(massimo, sum)


output.write(str(massimo))

input.close()
output.close()
