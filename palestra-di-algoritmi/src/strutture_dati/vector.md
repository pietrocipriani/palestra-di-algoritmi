# Vettori

I vettori in C++ sono dei contenitori (*container*) che si comportano in modo simile agli array, ma che hanno dimensione dinamica e possono essere ridimensionati. Per creare un vettore contenente elementi di tipo `TIPO` si scrive `vector<TIPO>`.

Memorizzano una serie di elementi uno dietro l'altro in memoria. È possibile accedere gli elementi in base all'_indice_: il numero dell'elemento (primo, secondo ecc).

I vector sono indicizzati da 0. Ossia il primo elemento corrisponde all'indice `0`, l'N-esimo elemento all'indice `N-1`.

## Inizializzazione

L'inizializzazione di una variabile di tipo `vector` si può fare nei seguenti modi (attenzione alle parentesi usate!):
- `vector<TIPO> nomeVariabile;` crea un vettore vuoto di elementi di tipo `TIPO` (ad es. `vector<float> valori`)
- `vector<TIPO> nomeVariabile(DIMENSIONE, VALORE);` crea un vettore con al suo interno il numero `DIMENSIONE` di elementi di tipo `TIPO` inizializzati al valore `VALORE` (ad es. `vector<int> classifica(158, 1)`)
- `vector<TIPO> nomeVariabile{ELEMENTO_1, ELEMENTO_2, ...};` crea un vettore di tipo `TIPO` contenente gli elementi `ELEMENTO_1`, `ELEMENTO_2`, ... (ad es. `vector<string> nomi{"Pippo", "Pluto", "Topolino"}`)

## Accesso

Per accedere agli elementi di un `vector` ci sono i seguenti modi:
- `v.at(posizione)` si usa per accedere all'elemento in posizione `posizione+1`, poichè gli indici partono da `0` (funziona come per gli array normali, ad es. `v.at(0)` restituisce il primo elemento)
- `v.front()` si usa per accedere al primo elemento
- `v.back()` si usa per accedere all'ultimo elemento

```cpp
vector<int> pesi{4, 7, 9, 8};
// scrive in output 4798 48
cout << pesi.at(0) << pesi.at(1) << pesi.at(2) << pesi.at(3)
	<< " " << pesi.front() << pesi.back() << endl;
```

## Aggiunta di elementi e ridimensionamento

- `v.push_back(ELEMENTO)` aggiunge `ELEMENTO` in fondo al vettore (ad es. `v.push_back(42.0)`)
- `v.resize(NUOVA_DIMENSIONE, VALORE)` ridimensiona il vettore così che abbia `NUOVA_DIMENSIONE` elementi. Se `NUOVA_DIMENSIONE` è maggiore della dimensione che aveva precedentemente, i nuovi elementi vengono inizializzati col valore `VALORE`. (ad es. `v.resize(1000, 0)`)
- `v.reserve(NUOVA_DIMENSIONE)` il vettore contiene ancora lo stesso numero di elementi precedenti, tuttavia ha allocato dello "spazio extra" per eventuali ridimensionamenti (vedasi dopo).
- `v.pop_back()` rimuove l'ultimo elemento del vettore
- `v.size()` restituisce il numero di elementi contenuti nel vettore

```cpp
vector<string> citta{"Trento", "Bolzano", "Milano", "Sorne"};
// scrive 4 Trento Sorne
cout << citta.size() << " " << citta.front() << " " << citta.back() << endl;

citta.push_back("Roma"); // aggiungi "Roma" in fondo
// scrive 5 Trento Roma
cout << citta.size() << " " << citta.front() << " " << citta.back() << endl;

citta.resize(2); // mantieni solo i primi 2 elementi
// scrive 2 Trento Bolzano
cout << citta.size() << " " << citta.front() << " " << citta.back() << endl;

citta.pop_back(); // rimuovi l'ultimo elemento, cioe' "Bolzano"
// scrive 1 Trento Trento
cout << citta.size() << " " << citta.front() << " " << citta.back() << endl;
```

### Osservazioni
<div class="info">
La variabile di tipo <code>vector</code> salva nello stack solo le informazioni utili a conoscere la dimensione effettiva del vettore e la posizione nello heap del vettore stesso.</br>
<code>vector</code> memorizza gli elementi uno dietro l'altro in un'area contigua di memoria heap.
</div>

Nella memoria heap abbiamo però detto che si può scrivere qualsiasi cosa, negli spazi vuoti.\
Ipotizziamo dunque di voler fare un `push_back` quando è già stato scritto qualcos'altro poco dopo la fine del nostro vettore: per potersi ingrandire, il `vector` è obbligato a dover cercare uno spazio vuoto più grande.\
Deve dunque **copiare** tutti gli elementi già presenti nella nuova area di memoria: ciò è MOLTO costoso, tuttavia il `vector` è stato pensato in modo da minimizzare il numero di ridimensionamenti, richiedendo un po' più di memoria.

Tuttavia è buona pratica, quando si conosce il numero di elementi, dire al vettore quanto spazio occupare. Abbiamo 3 modi per farlo:
- con il `reserve`: fintantochè il numero di elementi non supera la dimensione effettiva del vettore, chiamate a `push_back` non provocheranno nessuna copia (riallocamento).
- Con il `resize`: il vettore acquisisce effettivamente una dimensione di `DIMENSIONE`, eventuali `push_back` cercheranno di incrementare **ulteriormente** la dimensione. In questo caso dovete limitarvi ad **assegnare** gli elementi già presenti!
- In fase di dichiarazione, specificando `DIMENSIONE`. Valgono le stesse osservazioni di `resize`.

Vedremo più avanti altri modi di implementare una `list`a di elementi in modo da ovviare alla problematica dell'allocazione (vengono introdotti altri problemi).

<div class="info">
ndr: <code>list</code> in Python è un <i>array dinamico</i>: è implementato come un <code>vector</code>.
</div>

## Scorrere un vettore

Per scorrere tutti gli elementi di un `vector` si può usare un normale `for` come si farebbe per gli array normali. La variabile `i` del ciclo va da `0` a `numeri.size()` (non compreso) e quindi tocca, in ordine, tutti gli elementi di `numeri`.
```cpp
vector<float> numeri{3.14, 2.78, 1+2.1, 3*1.12};
for(int i = 0; i < numeri.size(); ++i) {
	cout << "In posizione " << i << " c'e' il numero " << numeri.at(i) << endl;
}
```

Vi è un altro modo di iterare gli elementi dei vari contenitori: 
```cpp
vector<float> numeri{3.14, 2.78, 1+2.1, 3*1.12};

// si legge come: "per ogni `numero` in `numeri`"
for (float numero : numeri) {
    // facciamo qualcosa con `numero`.
}
```
Tale modalità di iterazione potrà essere più efficiente per certi tipi di collezioni che vedremo più avanti.\
Tuttavia non permette di sapere a che elemento siamo arrivati (salvo contare manualmente in una variabile esterna).\
In questo caso è possibile fare la copia di `numero` senza troppi problemi, dato che è un `float`.\
Nel caso `numero` fosse stato di un tipo molto più "grosso" è sicuramente meglio predere un **riferimento** (`TIPO& numero`).

## Passare un vettore ad una funzione

Ovviamente i `vector` sono dei tipi come altri, quindi possono essere passati come parametro di una funzione senza problemi.\
Però, quando un parametro viene passato ad una funzione, esso viene copiato per fare in modo che la funzione non possa modificare la copia originale di quella variabile ma riceva una copia tutta per sè.\
Poichè i `vector` possono essere costosi da copiare, conviene prevenirlo mettendo una `&` dopo il tipo del parametro della funzione, per dire al compilatore di passare tale parametro *per reference*, ovvero non copiarlo.\
Però passare parametri alle funzioni senza copiarli può permettere alle funzioni di modificare le variabili che passiamo loro; se vogliamo evitare ciò (ad esempio perchè una funzione che scrive a schermo non deve modificare il contenuto del vettore che gli passiamo) possiamo mettere un `const` prima del tipo del parametro.
```cpp
// quando questa funzione viene chiamata, il vettore passato
// al posto di `v` viene copiato (operazione costosa)
void printVettore(vector<int> v) {
	for (int i = 0; i < v.size(); ++i) {
		cout << v << " ";
	}
	cout << endl;
}

// quando questa funzione viene chiamata, il vettore passato al posto
// di `v` non viene copiato ma la funzione ne ha accesso diretto
void printVettoreOttimizzato(const vector<int>& v) {
	v.push_back(5); // errore! `v` e' dichiarato const, quindi non puo' essere modificato 
	for (int i = 0; i < v.size(); ++i) {
		cout << v << " "; // tuttavia possiamo leggerlo liberamente.
	}
	cout << endl;
}

// questa funzione aggiunge un elemento sia ad `a` che a `b`, ma solo
// la modifica a b viene recepita dal chiamante, perche' a e'
// stato copiato prima di venir modificato, b invece no.
void modificaSecondoVettore(vector<int> a, vector<int>& b) {
	a.push_back(-1);
	b.push_back(-1);
	cout << "Vettore a in modificaSecondoVettore: ";    
	printVettoreOttimizzato(a);
	cout << "Vettore b in modificaSecondoVettore: ";
	printVettoreOttimizzato(b);
}

int main() {
	vector<int> a{0,1,2,3};
	vector<int> b{9,8,7};

	cout << "Vettore a all'inizio: ";
	printVettore(a); // a viene copiato, costoso!
	cout << "Vettore b all'inizio: ";
	printVettoreOttimizzato(b); // b non viene copiato

	modificaSecondoVettore(a, b);

	cout << "Vettore a nel main: ";
	printVettoreOttimizzato(a); // uguale all' a originale
	cout << "Vettore b nel main: ";
	printVettoreOttimizzato(b); // modificato
}
```

## Esercizi
- Scrivi un programma che chiede all'utente dei numeri finchè non viene inserito -1 e poi li scrive nell'ordine opposto in cui sono stati inseriti (attenzione agli indici!).
- Scrivi un programma che chiede all'utente dei numeri finchè non viene inserito -1, e ad ogni numero `i` che viene fornito dall'utente, scriva in output l`i-1`-esimo numero che l'utente ha inserito (oppure -1 se tale numero non esiste). Ad esempio, se inserisco, in ordine, `5 0 1 4 3`, il programma dovrebbe scrivermi, in ordine, `-1 5 0 -1 4`.
- Scrivi una funzione che, preso come parametro un vettore di numeri (attenzione a fare in modo che questo vettore non venga copiato), ne calcola il minimo e il massimo e li ritorna in un `pair<>`. La *signature* della funzione sarebbe quindi qualcosa come `pair<int, int> f(vector<int>& v)`.
- (difficile) Scrivi una funzione che calcola la lunghezza di una linea spezzata a partire dal vettore di punti che la compongono. Si possono fare infatti anche dei `vector` di `pair` in questo modo: `vector<pair<float, float>>`.

## Problemi

Questi problemi si possono probabilmente risolvere anche senza usare `vector`, ma cercate di usarlo per allenamento!
- Kattis: [peasoup](https://open.kattis.com/problems/peasoup), [missingnumbers](https://open.kattis.com/contests/wg4y5t/problems/missingnumbers), [eventplanning](https://open.kattis.com/problems/eventplanning), [basicprogramming1](https://open.kattis.com/problems/basicprogramming1)
