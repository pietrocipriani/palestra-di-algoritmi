# Curiosità & consigli
## IO
### `freopen`
Molte delle piattaforme di programmazione competitiva forniscono l'input in un file 'input.txt' e si aspettano l'output su 'output.txt'.\
È possibile reindirizzare `cin` e `cout` in modo che operino con __input.txt__.
Per fare ciò possiamo operare su `stdin` e `stdout`:
```cpp
  // Siamo nel main.
  
  // Chiude l'`stdin` originale e lo riapre in lettura ('r'ead) su "input.txt".
  freopen("input.txt", "r", stdin); // freopen: file re-open
  
  // Chiude l'`stdout` originale e lo riapre in lettura ('w'rite) su "output.txt".
  freopen("output.txt", "w", stdout);
```
### `sync_with_stdio(false)`
Per poter mischiare I/O C (`printf`, `scanf` ecc) con quello C++ (`cin`, `cout` ecc), il C++ ha previsto la sincronizzazione `stdin`/`cin` e `stdout`/`cout`.\
La sincronizzazione comporta la necessità da parte di `cin` e `cout` di leggere un solo dato per volta, senza poter dunque effettuare alcun buffering.\
Nel caso `cin` legga più del dovuto, una chiamata successiva a `scanf` potrebbe comportarsi in maniera errata, cominciando a leggere a partire dai byte non ancora letti.\
La mancanza di buffering, tuttavia, comporta che `cin` sia lento.\
Per ovviare a questo problema è possibile scrivere nel main:
```cpp
std::ios::sync_with_stdio(false);
```
per eliminare la sincronizzazione C/C++.\
In seguito a questa chiamata è **importante non mischiare funzioni IO di C con quelle di C++**.

### `tie`

`stdout` è di default 'block-buffered', non presenta a schermo immediatamente ciò che viene scritto, ma attende che venga riempito un buffer, in modo da ridurre in numero di chiamate di sistema effettive per la stampa.\
È possibile forzare lo svuotamento del buffer grazie a `cin << flush` oppure `fflush(stdout)`.\
Sia dato questo codice:
```cpp
cout << "Inserisci il numero di elementi: ";
cin >> num;
```
L'output effettivo a terminale è:
```
Inserisci il numero di elementi: 19

```
con `"19\n"` la stringa inserita dall'utente.\
Per quanto detto precedentemente, nel caso `"Inserisci il numero di elementi"` non riesca a riempire il buffer, dovrebbe essere possibile che venga richiesto l'input prima che venga stampato in output il prompt.\
Ciò non accade perchè `cin` forza il `flush` di `cout` prima di bloccarsi in attesa.\
Il `flush` in ambiente non interattivo è però inutile: serve solo nell'interazione con un utente.\
Si possono scollegare `cin` e `cout` scrivendo:
```cpp
cin.tie(nullptr);
```

## `vector<T>`
### `vector` & Python
È possibile accedere dal fondo un `vector<T> v` con la sintassi "stile Python":
```c++
v.end()[-1]
```
`v.end()` è un `vector<T>::iterator`.
La sintassi `ptr[i]` è equivalente a `*(ptr + i)`.\
`vector<T>::iterator` è un iteratore "random access" che pertanto può accedere in O(1) qualsiasi elemento e sfrutta l'algebra dei puntatori.

### Boundaries check
È possibile effettuare il check dei boundaries negli accessi ai `vector` rimpiazzando l'operatore `vector<T>::operator[int]` con il metodo `vector<T>::at(int)`:
```cpp
vettore[5];
vettore.at(5);
```
Il controllo dei boundaries è buona pratica soprattutto per evitare problematiche di sicurezza. Nell'ambito del competitive programming però comporta istruzioni da eseguire in più.\
È possibile compilare un codice C++ con la flag `-fsanitize=address -g` per individuare errori nell'accesso agli array (e vettori).
