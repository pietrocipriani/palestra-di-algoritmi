
input = open('input.txt', 'r')
output = open('output.txt', 'w')

# Numero di giorni
K = int(input.readline())

# Numero di persone
N = int(input.readline())

# Contenitore degli intervalli nella forma (inizio, fine).
intervalli = [ tuple( int(t) for t in line.strip().split(' ') ) for line in input.readlines() ]

# ordiniamo in base all'inizio.
def chiave_ordinamento(intervallo): return intervallo[0]

# Ordiniamo gli intervalli in modo da avere quelli che iniziano prima per primi.
# È una proprietà che verrà sfruttata dal resto dell'algoritmo.
intervalli.sort(key=chiave_ordinamento);

# Il primo tempo non ancora coperto.
inizio = 0;
# Il tempo massimo che possiamo coprire con gli intervalli già valutati.
fine = 0;

# Il numero di persone che devono essere assunte.
conteggio = 0;

for intervallo in intervalli:
    if intervallo[0] > inizio:
        # Sono finiti gli intervalli che ci permettono di dare continuità alla copertura.
        # Vediamo i precedenti fino a dove ci permettono di coprire.    

        # Dovremo iniziare a ricercare dal tempo appena successivo a quello di fine già trovato.
        inizio = fine + 1

        # Abbiamo assunto un'altra persona
        conteggio += 1

        # Possiamo lasciare `fine` invariato. Tanto è destinato a crescere.

    # `fine` deve essere un massimo.
    # Non è detto che la soluzione ottima debba avere per forza il massimo. Tuttavia:
    # - Se non contiene il massimo possiamo provare a sostituire il primo intervallo con il massimo ed ottenere una soluzione ottima valida.
    # - La ricerca dei successivi intervalli è un sottoproblema del tutto analogo, ma con tempo di inizio differente. Possiamo ripetere lo stesso ragionamento.
    # Questa tecnica di approccio è detta GREEDY, stiamo facendo una scelta "ingorda": "meglio abbondare che deficere".
    # Ovviamente questa tecnica non è sempre applicabile per ottenere soluzioni ottime.
    fine = max(fine, intervallo[1]);

    # Può tranquillamente succedere che finiscano gli intervalli senza che si esca dalla zona di copertura (ossia non si entra nell'if precedente).
    # Ciò può comportare che l'ultimo intervallo di copertura non venga conteggiato.
    # Gestiamo l'evento come caso particolare.
    # Ciò ci permette inoltre di terminare in anticipo.
    #
    # ES caso limite:
    # - Abbiamo coperto fino al giorno 50.
    # - C'è un intervallo che inizia al giorno 10 e termina al giorno 1000, ossia la fine delle vacanze.
    # - Senza questo if dovremmo continuare ad iterare tutti gli intervalli che cominciano fra il giorno 10 e il giorno 50 prima di accettare questo stesso intervallo.
    if fine >= K - 1:
        conteggio += 1
        break

output.write(str(conteggio))

input.close()
output.close()
