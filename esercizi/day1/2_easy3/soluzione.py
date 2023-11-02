

input = open('input.txt', 'r')
output = open('output.txt', 'w')

N = int(input.readline())

numbers = [ int(num) for num in input.readline().strip().split(' ') ]

assert(len(numbers) == N)

# Una somma pari può essere ottenuta come pari+pari o dispari+dispari.
# La somma massima è ottenuta dalla somma fra i due pari più grandi o i due dispari più grandi.


# `massimi[0]` è il massimo pari (non la somma, proprio l'elemento) trovato fino a questo momento.
# `massimi[1]` è il massimo dispari trovato fino a questo momento.
massimi = [-1 , -1]

# Somma massima pari trovata
somma_massima = -1

for num in numbers:
    # Come per la ricerca del massimo "standard", possiamo andare ad aggiornare `somma_massima` pian piano che valutiamo gli elementi.
    # Vogliamo che la `somma_massima` abbia sempre il valore della somma pari massima del sottovettore analizzato.

    # Esiste già un altro valore pari/dispari
    if massimi[num%2] >= 0:
        # Sommiamo `num` con il massimo nei valori pari/dispari precedenti.
        # Qualsiasi altra somma di `num` con gli altri valori pari/dispari precedenti sarà sicuramente minore (o uguale) di questa somma.
        # Aggiorniamo `somma_massima` se possibile.
        somma_massima = max(somma_massima, massimi[num%2] + num)

    # aggiorniamo `massimo` se possibile.
    massimi[num%2] = max(massimi[num%2], num);

output.write(str(somma_massima))

input.close()
output.close()
