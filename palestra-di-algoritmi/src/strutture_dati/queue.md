# Code

Le _code_ sono dei *container* che funzionano come le code ai negozi: quando arrivano delle nuove persone si mettono in fondo alla coda, e nel momento in cui il negozio ammette nuove persone quelle che entrano sono quelle in cima alla coda.\
Le operazioni supportate sono quindi quelle per aggiungere in fondo e per togliere dalla cima.\
In C++ si può creare una coda di tipo `TIPO` usando `queue<TIPO>`, ad esempio `queue<string>`.  Le `queue` supportano le seguenti operazioni:
- `q.push(ELEMENTO)` per aggiungere `ELEMENTO` (di tipo `TIPO`) in fondo alla coda
- `q.front()` per leggere l'elemento in cima alla coda
- `q.pop()` per rimuovere l'elemento in cima alla coda
- `q.size()` restituisce il numero di elementi in coda

<div class="warning">
Il <code>vector</code> NON deve essere usato come una <code>queue</code>.</br>
Sebbene l'interfaccia metta a disposizione la funzione <code>erase</code>, questa ha complessità O(N) quando effettuata all'inizio del vettore (rispetto all'O(1) di <code>queue::pop()</code>).</br>
Questo è dovuto al fatto che il <code>vector</code> vuole memorizzare tutti gli elementi in un array partendo da una posizione ben stabilita. Eliminare un elemento all'inizio comporta lo spostamento (<i>shifting</i>) di tutti gli altri elementi.
</div>

```cpp
queue<int> q;
q.push(5);
q.push(6);
q.push(7);

// scrive 3 5
cout << q.size() << " " << q.front() << endl;

q.pop();
// scrive 2 6
cout << q.size() << " " << q.front() << endl;
```

## Problemi

- Kattis: [ferryloading3](https://open.kattis.com/problems/ferryloading3)
