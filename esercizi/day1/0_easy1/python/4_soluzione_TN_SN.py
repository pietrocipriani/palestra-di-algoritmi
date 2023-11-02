


input = open("input.txt", "r")
output = open("output.txt", "w")

# Numero di elementi: parametro del problema
N = int(input.readline())

# Leggo la riga degli S.
Ss = [ int(S) for S in input.readline().strip().split(' ') ]

# Utilizzo la funzione builtin di Python.
# Questa soluzione non è didattica: non permette di ragionare su come implementare il `max`.
massimo = max(Ss)

# Stampiamo il massimo.
output.write(str(massimo))

input.close()
output.close()
