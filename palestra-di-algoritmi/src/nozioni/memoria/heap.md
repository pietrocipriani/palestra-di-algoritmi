# Memoria Heap

La parola "heap" significa "mucchio".\
Potete pensare questa memoria come un foglio bianco, dove potete disegnare e scrivere dove c'è spazio. Scrivete a matita, in modo che quando qualcosa non serve più sia possibile cancellarla per liberare spazio.

Dal momento che abbiamo una "accozzaglia" di elementi, come facciamo a rintracciare quelli che ci servono? Ci salviamo la loro posizione nello stack, che è molto più ordinato.

L'idea è che quando un elemento non ci serve più debba essere cancellato per liberare spazio.

All'interno del corso non utilizzeremo la memoria Heap direttamente, tuttavia impiegheremo delle strutture dati (contenitori di elementi) che la utilizzano.\
Tali strutture dati, tuttavia, lo gestiscono autonomamente.\
L'Heap è stato introdotto solo per giustificare il costo di certe operazioni, per il resto possiamo far finta che non esista.
