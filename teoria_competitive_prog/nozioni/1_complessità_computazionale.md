# Complessità computazionale

<div class="warning">
Questa è una trattazione informale, dato che l'utilizzo della notazione matematica potrebbe risultare un po' troppo pesante.
</div>

Molte piattaforme per la programmazione competitiva pongono dei **limiti di tempo e di spazio** agli algoritmi.\
Rendere la vita complicata ad algoritmi poco efficienti è proprio l'obiettivo di queste competizioni!

<div class="warning">
Una trattazione approfondita sulla complessità richiede una buonissima conoscenza dell'architettura della macchina, del compilatore ecc...:
<ul>
<li> Istruzioni differenti possono impiegare un quantitativo di cicli di clock differenti.</li>
<li> Macchine differenti possono impiegare cicli di clock differenti per una stessa istruzione.</li>
<li> Un compilatore potrebbe ottimizzare la lettura e scrittura delle variabili "salvandole sul processore", che ha poco spazio, ma che è in grado di azzerare le tempistiche di lettura e scrittura</li>
<li> La memoria non è solo la RAM. Fra processore e RAM vi sono le cosiddette caches (L1, L2 e L3) che sono delle memorie poste in maniera gerarchica, più rapide, ma per questioni di costi sono anche più piccole. Dalla RAM non vengono letti solo i byte che ci servono, ma anche un bel po' di quelli "vicini" in modo da salvarli nelle cache. Vi sono alcuni algoritmi che accedono sequenzialmente la memoria che sono più veloci di altri algoritmi che invece accedono alla memoria saltando da parte a parte.</li>
</ul>
</div>

La nostra concezione di complessità computazionale non sarà dunque mirata ad avere una formula esatta per calcolare il tempo impiegato dal calcolatore, ma si limiterà a stimare l'**andamento del tempo di esecuzione al crescere della dimensione** dell'input.

Chiameremo `N` la "dimensione dell'input", il nome potrebbe variare in base al problema. Alcuni problemi potrebbero avere "più dimensioni".

## Casi ottimo, pessimo e medio
Dati due input di **uguale dimensione** NON è detto che uno **stesso algoritmo** impieghi lo stesso tempo.\
Ci sono alcuni input "più buoni di altri". I cosiddetti **caso ottimo**, **caso medio** e **caso pessimo** possono avere complessità differenti.

Per esempio, dato un algoritmo per la ricerca di un `elemento` in un `vector`:
```cpp
bool contiene(const vector<int>& v, int elemento) {
    for (int e : v) {
        if (e == elemento) {
            // Il return termina l'esecuzione della funzione.
            return true;
        }
    }
    return false;
}
```
`N` è la dimensione di `v` (`v.size()`).\
È possibile osservare che se l'elemento da cercare è in prima posizione, allora l'algoritmo terminerà subito. Questo è il caso **ottimo**.\
Se l'elemento da cercare è in ultima posizione (o non esiste) allora l'algoritmo deve scorrere tutto il vettore prima di terminare. Questo è il caso **pessimo**.\
Negli altri casi, in media, l'`elemento` si troverà all'incirca a metà del vettore. Questo NON è il caso **medio**.

Il caso medio deve comprendere anche il caso ottimo e il caso pessimo. Tuttavia la media è relativa alla frequenza con cui possono avvenire certi eventi.
In particolare bisognerebbe conoscere la probabilità con cui un elemento non si trova all'interno del vettore per conoscere l'impatto del caso pessimo.
Non possiamo nemmeno dare per scontato che tutti gli elementi abbiano la stessa probabilità di dover essere cercati.

Il caso medio è spesso intrattabile.\
Per quanto riguarda il caso ottimo: non possiamo aspettarci che il CMS (il programma che valuterà le soluzioni) sia così gentile da darci solo casi ottimi.\
Quindi il nostro obiettivo sarà quello di ottimizzare il **caso pessimo**.

## Come stabilire la classe di complessità

L'algoritmo per la ricerca dell'elemento qui sopra, nel caso pessimo esegue le istruzioni nel ciclo `N` volte.\
Facciamo che le istruzioni all'interno del ciclo impieghino un tempo `a`. Allora il tempo impiegato dal ciclo è di `N·a`.\
Facciamo che le istruzioni all'esterno del ciclo impieghino un tempo `b`. Allora il tempo complessivo impiegato dalla funzione è `b + N·a`

Il nostro scopo è vedere come si comporta la funzione per input MOOOLTO grandi: se N "diventa infinito" allora è intuitivo pensare che aggiungere una costante `b` sia ininfluente.\
Quindi possiamo approssimare il tempo complessivo impiegato dalla funzione come `N·a`.

Dal momento che, come detto precedentemente, non è così semplice calcolare il valore di `a`, possiamo tralasciare questa informazione. Otteniamo dunque `N`.\
Indichiamo il fatto che si stia parlando di una approssimazione con la notazione **Θ(N)** (Potreste trovarlo scritto come O(N) per comodità. Le due notazioni NON sono equivalenti, ma per i nostri scopi possono essere interscambiate).

Θ(N) non ci dice quanto ci metterà il nostro algoritmo, ma ci dà una buona indicazione di come cresce il tempo al crescere di `N`.\
Con ragionamenti analoghi si può osservare che il **caso ottimo** è Θ(1). Il **caso medio**, sotto determinate ipotesi, è Θ(N).

Possiamo creare una **gerarchia** fra le varie _classi di complessità_ ("migliori" a sinistra).\
Dal momento che una delle approssimazioni prevede "`N` molto grande", è chiaro che tale gerarchia non ci dia nessuna informazione su quale sia l'algoritmo migliore per `N` piccolo:\
\\[ \Theta(1) \ll \Theta(logN) \ll \Theta(N) \ll \Theta(N·logN) \ll \Theta(N^a) \ll \Theta(b^N) \ll \Theta(N!) \ll \Theta(N^N) \\]

`logN` è detto "logaritmo di N", è una funzione che molti di voi probabilmente non conoscono. Tuttavia è sufficiente sapere che è una funzione che cresce molto lentamente.\
`N!` è detto "N fattoriale" e significa `N·(N-1)·(N-2)· ... · 1`. È una funzione che cresce molto velocemente. Tuttavia non quanto `N^N`.

Durante il corso le classi di complessità potrebbero essere chiamate con questi nomi:
- Θ(1)      : _costante_
- Θ(logN)   : _logaritmica_
- Θ(N)      : _lineare_
- Θ(N·logN) : _quasi-lineare_
- Θ(N^a)    : _polinomiale_
- Θ(b^N)    : _esponenziale_
- Θ(N!)     : _fattoriale_

Vi sono anche altre classi. A noi interessano principalmente fino alla _polinomiale_. Non dovete impararle a memoria. Continueremo ad usare questi termini: prima o poi ve li ricorderete.

Vi invito ad usare calcolatrici grafiche ([geogebra](https://www.geogebra.org/calculator), [desmos](https://www.desmos.com/calculator) ecc) per visualizzare l'andamento delle varie funzioni.\
Potete anche inserire dei coefficienti per osservare che a lungo andare non cambiano la situazione.
