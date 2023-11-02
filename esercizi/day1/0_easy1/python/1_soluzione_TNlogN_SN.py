


input = open("input.txt", "r")
output = open("output.txt", "w")

# Numero di elementi: parametro del problema
N = int(input.readline())

# Leggo la riga degli S.
Ss = [ int(S) for S in input.readline().strip().split(' ') ]

Ss.sort()

output.write(str(Ss[-1]))

input.close()
output.close()
