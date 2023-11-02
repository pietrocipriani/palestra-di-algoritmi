
class Veicolo:
    def __init__(self, posti, numero, costo):
        # numero di posti nel veicolo
        self.posti = posti
        # numero di veicoli disponibili
        self.numero = numero
        # costo del veicolo
        self.costo = costo

input = open('input.txt', 'r')
output = open('output.txt', 'w')

N = int(input.readline())

veicoli = input.readlines()
veicoli = [ [ int(v) for v in line.strip().split() ] for line in veicoli ]
# Lista contenente i veicoli.
veicoli = [ Veicolo(posti, numero, costo) for posti,[numero,costo] in zip([2,4,5,7], veicoli) ]

# Il risultato che vogliamo migliorare pian piano.
# Sappiamo già che non possono essere superati i 100·100 euro (si può raffinare ancora di più la stima).
costo_minimo = 100 * 100;

# Funzione RICORSIVA per il calcolo delle combinazioni.
# `indice_veicolo` è l'indice del primo veicolo che possiamo prendere.
# `persone_rimanenti` è il numero di persone che sono ancora in attesa.
# `costo_attuale` sono i soldi già spesi.
def combinazioni(indice_veicolo, persone_rimanenti, costo_attuale):
    global costo_minimo

    # Se non ci sono più persone in attesa allora abbiamo concluso.
    if persone_rimanenti <= 0:
        # Aggiorniamo il costo ottenuto, se necessario.
        costo_minimo = min(costo_minimo, costo_attuale)
        # Torniamo indietro per provare un'altra possibilità.
        return

    # Se sono finiti i veicoli (ma non le persone) allora non siamo giunti ad una soluzione. Torniamo indietro.
    if indice_veicolo >= len(veicoli):
        return

    # Salviamo il veicolo per riferimento! In modo da accedervi direttamente.
    veicolo = veicoli[indice_veicolo]

    # Possiamo prendere i veicoli di una certa tipologia tutti in uno stesso momento.
    # Prenderli prima o dopo non fa differenza dato che il costo è sempre quello e anche se sono mezzi vuoti non cambia nulla.
  
    # Cerchiamo di prendere più veicoli migliori possibili, per cercare una soluzione "buona".
    # Possiamo anche prendere 0 veicoli di questo tipo.
    for numero in range(veicolo.numero, -1, -1):
        # Proviamo a soddisfare le altre persone con i prossimi veicoli.
        # Non ha senso riprovare ad utilizzare questo veicolo (o precedenti) dato che è equivalente a prenderne di più in questo momento. Ma abbiamo già provato a prenderne di più.
        # Abbiamo soddisfatto al massimo `veicolo.posti * numero` persone. Anche se andiamo in negativo non è un problema.
        # Abbiamo speso ulteriori `veicolo.costo * numero` euro.
        combinazioni(indice_veicolo + 1, persone_rimanenti - veicolo.posti * numero, costo_attuale + veicolo.costo * numero)


# Proviamo le varie combinazioni.
# Partiamo dal veicolo 0. Dobbiamo trasportare `N` persone. Abbiamo già speso 0 euro.
combinazioni(0, N, 0);

output.write(str(costo_minimo));

input.close()
output.close()
