


input = open("input.txt", "r")
output = open("output.txt", "w")

# Numero di elementi: parametro del problema
N = int(input.readline())

# Leggo la riga degli S.
Ss = [ int(S) for S in input.readline().strip().split(' ') ]

# Inizializzo il massimo con il primo elemento: rappresenta il massimo del sottovettore [0:1]
massimo = Ss[0]

for S in Ss[1:]:
    # Ad ogni iterazione `massimo` contiene il massimo fra gli elementi già valutati.
    massimo = max(massimo, S)

# `massimo` a questo punto contiene il massimo di `Ss`.
output.write(str(massimo))

input.close()
output.close()
