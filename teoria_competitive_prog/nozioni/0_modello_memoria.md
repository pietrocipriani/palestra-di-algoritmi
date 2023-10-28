# La gestione della memoria nei programmi.

La memoria (virtuale) di un programma è suddivisa in "segmenti" con significati e scopi differenti.

Ai fini del corso ne andremo a vedere solo 2: lo _stack_ e lo _heap_. Ve ne sono altri.

## Stack dei record di attivazione.

La parola "stack" significa "pila" (nel senso di oggetti uno sopra l'altro.)\
In particolare gli oggetti che vengono impilati sono i "record di attivazione" delle funzioni:
Ogni funzione contiene al suo interno delle variabili. Le variabili devono memorizzare dei dati, e per fare ciò necessitano di memoria.
Ogni chiamata di funzione è dunque associata ad una "scatoletta" (_record di attivazione_) di dimensione adeguata a contenere tutte le variabili della funzione.
Tale scatoletta viene "impilata" quando viene chiamata la funzione e viene "distrutta" quando la funzione termina.\
L'idea è che alla funzione non interessi nulla di chi l'ha chiamata ecc, e che effettui le operazioni nella sua scatoletta, indipendentemente dalla posizione di questa nello stack.

Lo stack è limitato. In ambiente GNU/Linux arriva di default a 8 MegaByte. È possibile estenderlo, tuttavia non avrete la possibilità di fare ciò con il CMS (il programma che valuterà i vostri algoritmi).\
Bisogna pertanto stare attenti alle funzioni ricorsive!\

Bisogna stare attenti anche a non allocare variabili troppo grandi, come array nello stack:
```
void foo() {
    int N = ...;
    int array[N];
}
```
Oltre a dipendere da un `N` "esterno" che può diventare molto grande, questa scrittura è letteralmente **VIETATA** dallo standard ISO di C++.
Un `array` di questo tipo è detto _VLA_ (variable length array) ed è stato introdotto in C99 (sono stati fatti passi indietro in C11). In C++ non è mai stato introdotto.
Sebbene sia vietato, è supportato da quasi tutti i compilatori "principali".

Vedremo come alternative il `vector`.

L'idea è che i _contenitori_ di elementi (array, liste ecc) debbano essere salvati nella memoria _Heap_.

## Memoria Heap

La parola "heap" significa "mucchio".
Potete pensare questa memoria come un foglio bianco, dove potete disegnare e scrivere dove c'è spazio. Scrivete a matita, in modo che quando qualcosa non serve più sia possibile cancellarla per liberare spazio.

Dal momento che abbiamo una "accozzaglia" di elementi, come facciamo a rintracciare quelli che ci servono? Ci salviamo la loro posizione nello stack, che è molto più ordinato.

L'idea è che quando un elemento non ci serve più debba essere cancellato per liberare spazio.

All'interno del corso non utilizzeremo la memoria Heap direttamente, tuttavia impiegheremo delle strutture dati (contenitori di elementi) che la utilizzano.\
Tali strutture dati, tuttavia, lo gestiscono autonomamente.
L'Heap è stato introdotto solo per giustificare il costo di certe operazioni, per il resto possiamo far finta che non esista.
