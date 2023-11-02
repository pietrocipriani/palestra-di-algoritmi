

input = open('input.txt', 'r')
output = open('output.txt', 'w')

G, P = (int(num) for num in input.readline().strip().split(' '))

# L'algoritmo è una simulazione della spartizione.
  
# Numero di gemme date a Totò. Inizialmente Totò non ne ha nessuna.
gemme_toto = 0

# Numero di gemme da dare a Totò in questa iterazione.
gemme_da_dare_a_toto = 1
  
# Finchè ci sono gemme andiamo avanti con la simulazione.
while G > 0:
    # Le gemme potrebbero non essere sufficienti: eventualmente Totò prende tutte le rimanenti.
    gemme_toto += min(G, gemme_da_dare_a_toto);

    # Togliamo le gemme dell'iterazione. Anche se andiamo sotto zero non è un problema.
    # Gli altri si prendono complessivamente `P-1` gemme.
    G -= gemme_da_dare_a_toto + (P - 1);

    # All'iterazione successiva Totò prende una gemma in più.
    gemme_da_dare_a_toto += 1

output.write(str(gemme_toto))

# Si può dimostrare che questo algoritmo è un Θ(sqrt(G + P²) - P) dal punto di vista della complessità temporale.

input.close()
output.close()
