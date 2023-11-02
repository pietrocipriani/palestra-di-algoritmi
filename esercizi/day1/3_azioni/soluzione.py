
input = open('input.txt', 'r')
output = open('output.txt', 'w')

N = int(input.readline())

# Massima differenza incontrata fino a questo momento.
# Il problema non specifica quale debba essere l'output nel caso di N=1 (nessuna differenza).
# La differenza (in valore assoluto) è >= 0, quindi possiamo tranquillamente inizializzare a 0.
max_diff = 0;

# valore precedente. Per calcolare la differenza.
prev = int(input.readline())

for raw in input.readlines():
    # nuovo valore.
    num = int(raw)

    # differenza in valore assoluto.
    diff = abs(prev - num)

    # aggiorniamo la differenza se necessario.
    max_diff = max(max_diff, diff)

    # il valore attuale diventa il prossimo "valore precedente".
    prev = num
  
output.write(str(max_diff))

input.close()
output.close()
