BACKTRACKING

Facciamo finta di dover trovare tutte le sequenze formate da 4 palline che chiameremo `a`, `b`, `c` e `d`.\
Indichiamo il sacchetto delle palline con `{a, b, c, d}`
Modellizziamo il problema dal punto di vista delle **scelte**:\
- Inizialmente abbiamo una sequenza nulla, possiamo selezionare una qualsiasi delle palline dal sacchetto. Abbiamo 4 possibilità.\
- Facciamo finta di aver selezionato la pallina `a`, otteniamo una sequenza `a` e nel sacchetto rimangono `{b, c, d}`.
- Per la seconda pallina scegliamo `b`, sequenza `ab` e sacchetto `{c, d}`.
- Esaurendo le scelte otteniamo `abcd` con sacchetto `{}`. Abbiamo ottenuto la prima sequenza completa.
- Torniamo indietro, rimuoviamo `d` ottenendo `abc` e `{d}`. Non abbiamo altre scelte, torniamo ancora indietro ed otteniamo `ab` e `{c, d}`.
- A questo punto possiamo fare un'altra scelta: selezioniamo prima `d`, ottenendo `abd` e `{c}` e poi abbiamo la scelta obbligata che ci porta ad ottenere `abdc`.
- Possiamo ripetere questo "tornare indietro e provare altre scelte" per ottenere tutte le possibili soluzioni.

Chiamiamo questo algoritmo _backtracking_.

Da un punto di vista implementativo il "tornare indietro" si può implementare con **funzioni ricorsive**.

Viene utilizzato sia per problemi di **esplorazione** (proviamo tutte le possibilità per trovare le varie soluzioni e poi valutarle) sia problemi **enumerativi** (dobbiamo elencare tutte le possibilità).

La tecnica _backtracking_ è tendenzialmente inefficiente (produce soluzioni super esponenziali), tuttavia può essere un punto di partenza da raffinare.

Un algoritmo generico può essere espresso da questo skeleton:
```c++
// Questo è un pseudocodice. Non è scritto in C++.

// Prendiamo i dati del problema, la soluzione (sequenza di scelte parziali) e dati derivati in seguito alle scelte.
backtracking(dati_problema, soluzione_parziale, dati_parziali, ...) {
    // Non ci sono più scelte disponibili oppure abbiamo un altro modo per stabilire se siamo giunti in una soluzione.
    if (fine(...)) {
        // Siamo giunti ad una "soluzione", gestiamola.
        return processa_soluzione(...);
    }

    // Generiamo le possibili scelte che possiamo fare in base allo stato attuale.
    possibili_scelte = genera_scelte(...);

    // Proviamo tutte le scelte.
    for (scelta : possibili_scelte) {
        // Facciamo tutte le modifiche comportate dalla scelta
        effettua_scelta(scelta);

        // Salviamo il valore di ritorno del sottoproblema in seguito a questa scelta, possiamo gestirlo oppure anche non fare nulla, dipende dal problema.
        auto result = backtracking(dati_problema, soluzione_parziale_aggiornata, dati_parziali_aggiornati, ...);

        // Ripristiniamo le modifiche comportate dalla scelta (se non locali).
        ripristina_scelta(scelta);
    }
}
```

Per esempio:
#### LAUREA
```cpp
// Lista contenente i 4 tipi di veicolo.
// Veicolo: contiene `numero` di veicoli di una certa categoria, `costo` e numero di `posti`.
std::vector<Veicolo> veicoli = ...;

// La soluzione migliore trovata fino a questo momento.
int costo_minimo = std::numeric_limits<int>::max();

// Funzione ricorsiva che implementa il backtracking.
// Ha accesso ai vari `veicoli`, al numero di persone rimaste in attesa e ai soldi spesi fino a questo momento.
void laurea(int persone_in_attesa, int soldi_spesi) {
    // Non ci sono più persone in attesa, non dobbiamo spendere nient'altro.
    // Il numero di persone in attesa può essere negativo:
    // ci permette di evitare di gestire a parte casi con veicoli più grandi del numero di persone rimanenti,
    // tanto il risultato è lo stesso in termini economici.
    if (persone_in_attesa <= 0) {
        // Il valore associato a questa soluzione è il numero di `soldi_spesi` (è la quantità che vogliamo minimizzare).
        // Aggiorniamo la soluzione ottima.
        costo_minimo = std::min(costo_minimo, soldi_spesi);
        return;
    }

    // Possiamo scegliere uno qualsiasi dei veicoli disponibili.
    for (const Veicolo& veicolo : veicoli) {
        if (veicolo.numero <= 0) continue;

        // "Consumiamo" un veicolo.
        --veicolo.numero;

        // Cerchiamo la soluzione migliore per le persone e i veicoli rimanenti.
        laurea(persone_in_attesa - veicolo.posti, soldi_spesi + veicolo.costo);

        // Ripristiniamo l'uso del veicolo.
        ++veicolo.numero;
    }
}
```

### DOMINO
```cpp
// Sacchetto delle tessere.
std::vector<Tessera> tessere = ...;
// Rimuovere e riaggiungere elementi ai vector è impegnativo, soprattutto se non fatto alla fine.
// Semplicmente segnamo le tessere come usate. Inizialmente non è stata usata alcuna tessera.
std::vector<bool> tessere_usate(N, false);

// Funzione ricorsiva che implementa il backtracking.
// Abbiamo accesso alle tessere rimanenti. Ci interessa l'estremo a cui attaccare le altre tessere.
// In questo esempio propaghiamo la soluzione all'indietro: si poteva fare anche in `laurea`.
// Il domino può iniziare con qualsiasi `estremo`: ce lo giochiamo esternamente provando tutte le possibilità.
int domino(int estremo) {
    // Non abbiamo una soluzione finale.
    // Semplicemente se non riusciamo a fare nessun'altra scelta allora la sequenza successiva attaccabile più lunga sarà lunga 0.
    
    // La lunghezza massima della sequenza attaccabile.
    int massima_lunghezza_attaccabile = 0;

    // Possiamo scegliere fra una qualsiasi delle tessere attaccabili e non ancora utilizzata.
    for (int i = 0; i < N; ++i) {
        // Se la tessera è già stata usata o se non è attaccabile allora non la possiamo scegliere.
        if (tessere_usate.at(i) || non_attaccabile(estremo, tessere.at(i))) continue;

        // Segnamo la tessera come usata.
        tessere_usate.at(i) = true;

        // Prendiamo la lunghezza massima costruibile usando questa tessera. +1 dovuto a questa tessera.
        int lunghezza = domino(estremo_opposto(estremo, tessere.at(i))) + 1;

        // Aggiorniamo la massima lunghezza.
        massima_lunghezza_attaccabile = std::max(massima_lunghezza_attaccabile, lunghezza);

        // Ripristiniamo la tessera.
        tessere_usate.at(i) = false;
    }

    // È ancora a 0 se non siamo riusciti ad attaccare alcuna tessera.
    return massima_lunghezza_attaccabile;
}

```
