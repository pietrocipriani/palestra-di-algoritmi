# Creiamo una MATRICE (ossia una tabella 7x7). Può essere vista come lista di liste (righe).
# Nella cella (y, x) andiamo a contare quante tessere y-x e x-y abbiamo (ancora) disponibili.
tessere = [ [0 for _ in range(7) ] for _ in range(7) ]

# Con "backtracking" si intende "provare tutte le combinazioni per poi tornare indietro e provarne altre".
# È una tecnica che viene implementata con funzioni RICORSIVE.
# È proprio quello che fa il nostro algoritmo.
# `numero` è il valore del primo estremo, per poterci collegare alla catena già creata.
def backtracking(estremo):

    # Salviamo la riga delle tessere `numero`-? per facilità di accesso.
    riga = tessere[estremo]

    # Dobbiamo ricercare un massimo. Questa è la lunghezza massima parziale della sequenza costruibile con le tessere rimanenti e iniziando con `numero`.
    # Inizializziamo a 0 perchè è l'evenienza in cui non sia possibile collegare nessun'altra tessera.
    massima_lunghezza = 0

    # Proviamo un qualsiasi altro estremo.
    for altro_estremo in range(7):
        # Se non è rimasta nessuna tessera `numero`-`altro_numero` allora non possiamo proseguire.
        if riga[altro_estremo] <= 0: continue

        # Stiamo usando una tessera `numero`-`altro_numero`. Non sarà più possibile impiegarla in futuro.
        tessere[altro_estremo][estremo] = --riga[altro_estremo]

        # Aggiorniamo la lunghezza massima se possibile.
        # Proviamo tutte le combinazioni sapendo che si devono collegare ad `altro_numero`.
        # Il +1 serve a conteggiare anche la tessera `numero`-`altro_numero` che abbiamo aggiunto qui.
        massima_lunghezza = max(massima_lunghezza, backtracking(altro_estremo) + 1)

        # Torniamo indietro per provare altre possibilità.
        # Rimettiamo la tessera `numero`-`altro_numero` nel sacchetto delle tessere.
        tessere[altro_estremo][estremo] = ++riga[altro_estremo]

    # Ritorniamo la lunghezza massima. Eventualmente 0 se non siamo riusciti ad aggiungere nessun'altra tessera.
    return massima_lunghezza

input = open('input.txt', 'r')
output = open('output.txt', 'w')

# Numero di tessere
N = int(input.readline())

for i in range(N):
    a,b = ( int(num) for num in input.readline().strip().split(' ') )
    
    # Incrementiamo il conteggio sia delle tessere a-b che delle tessere b-a. Tanto possiamo girare questa tessera a piacimento.
    #
    # L'operatore ++(...) permette di incrementare `tessere.at(b).at(a)` e restituisce il valore post incremento.
    # Valore che poi viene assegnato a `tessere.at(a).at(b)`.
    tessere[a][b] = ++tessere[b][a]

# Ricerca della lunghezza massima.
massima_lunghezza = 0

# Possiamo partire con una cella qualsiasi.
# Sfruttiamo la funzione `bruteforce` e "facciamo finta" di vincolare uno degli estremi delle tessere. Tuttavia li proviamo tutti.
for i in range(7):
    # Aggiorniamo la lunghezza massima se necessario.
    # Chiamiamo bruteforce in modo che inizi con l'estremo `i`.
    #
    # Qui non c'è il +1 perchè non abbiamo aggiunto nessuna tessera.
    massima_lunghezza = max(massima_lunghezza, backtracking(i))


output.write(str(massima_lunghezza))

input.close()
output.close()
