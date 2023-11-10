# Stack dei record di attivazione.

La parola "stack" significa "pila" (nel senso di oggetti uno sopra l'altro.)\
In particolare gli oggetti che vengono impilati sono i "**record di attivazione**" delle funzioni:\
Ogni funzione contiene al suo interno delle variabili. Le variabili devono memorizzare dei dati, e per fare ciò necessitano di memoria.\
Ogni chiamata di funzione è dunque associata ad una "**scatoletta**" (_record di attivazione_) di dimensione adeguata a contenere tutte le variabili della funzione.\
Tale scatoletta viene "impilata" quando viene chiamata la funzione e viene "distrutta" quando la funzione termina.\
L'idea è che alla funzione non interessi nulla di chi l'ha chiamata ecc, e che effettui le operazioni nella sua scatoletta, indipendentemente dalla posizione di questa nello stack.

<div class="warning">
<b>Lo stack è limitato</b>. In ambiente GNU/Linux arriva di default a 8 MegaByte. È possibile estenderlo, tuttavia non avrete la possibilità di fare ciò con il CMS (il programma che valuterà i vostri algoritmi).</br>
Bisogna pertanto stare attenti alle funzioni ricorsive!
</div>

Bisogna stare attenti anche a non allocare variabili troppo grandi, come array nello stack:
```cpp
void foo() {
    int N = ...;
    int array[N];
}
```
<div class="warning">
Oltre a dipendere da un <code>N</code> "esterno" che può diventare molto grande, questa scrittura è letteralmente <b>VIETATA</b> dallo standard ISO di C++.</br>
Un <code>array</code> di questo tipo è detto <i>VLA</i> (variable length array) ed è stato introdotto solo in C e non in C++.</br>
Sebbene sia vietato, è supportato da quasi tutti i compilatori "principali".
</div>

Vedremo come alternative il `vector`.

L'idea è che i _contenitori_ di elementi (array, liste ecc) debbano essere salvati nella memoria _Heap_.

