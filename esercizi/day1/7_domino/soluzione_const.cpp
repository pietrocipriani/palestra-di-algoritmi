#include <bits/stdc++.h>
using namespace std;

// È possibile effettuare alcune osservazioni per migliorare la soluzione.
//
// Se vengono impiegate un certo numero di tessere [a b] (non contiamo le [b a]), allora la sequenza avrà la forma:
// [? ... a][a b][b ... a][a b][b ... a][a b][b ... a][a b][b ... ?]
//
// Con [b ... a] si intende una sequenza di lunghezza arbitraria che inizia per `b` e finisce per `a`.
//
// È possibile osservare che esiste una soluzione di uguale lunghezza che impiega le stesse tessere:
// [? ... a][a b][b a][a b][b a][a ... b][b ... a][a ... b][b ... ?]
//
// Dove [a ... b] è dato da uno dei [b ... a] specchiato (possono essere impiegate le stesse identiche tessere).
//
// Non ha senso dunque portare avanti tante tessere [a b] dato che possiamo ottenere soluzioni di lunghezza identica giocandoci quasi tutte le tessere non appena incontriamo una `a`.
// Inoltre ha senso giocarsi più tessere [a b] possibili, dato che [a b][b a] ci permette di aggiungere 2 tessere senza però modificare l'estremo:
//   Se prima avevamo un [? ... a][a ... ?] allora sicuramente [? ... a][a b][b a][a ... ?] sarà una sequenza valida più lunga.
//
// Tuttavia una tessera [a b] può anche essere impiegata come [b a].
//
// Considerando che le coppie di tessere [a b][b a] possono essere "semplificate" (dato che, come detto 2 righe più sopra possiamo tranquillamente appiccicare la sottosequenza destra e sinistra assieme).
// Possiamo avere al massimo 3 tessere di ogni tipo:
//   Se ci sono un numero pari di tessere [a b] allora è come averne 0, se dispari allora ne rimane 1. Analogo per [b a].
//   Se ci sono un numero dispari di tessere [a b]/[b a] può succedere che una tessera non venga utilizzata e che rimangano una tessera [a b] e una [b a] per un totale di 3 tessere.
//
// Dobbiamo inoltre considerare che possiamo appiccicare tutte le tessere del tipo [a a] non appena otteniamo una `a`:
//   Non usarle significa sequenze più brevi.
//   Usarle successivamente non cambia nulla: [? ... a][a a][a ... a][a ... ?] = [? ... a][a ... a][a a][a ... ?]
//
// Quindi le tessere che ci interessano sono quelle del tipo [a b] con `a != b`. Ma queste sono 21.
// Quindi possiamo ricondurre un qualsiasi problema con N tessere ad un problema di massimo 63 tessere (3 per ogni tessera [a b]).
// Questo significa che non abbiamo dipendenza da N e, a parte per la fase di lettura e costruzione della matrice in O(N), l'algoritmo è O(1).
// 
// ATTENZIONE: O(1) significa solamente che la complessità dell'algoritmo non dipende dall'input, non che l'algoritmo sia molto veloce.
// Infatti anche il problema con 63 tessere è parecchio impegnativo.
// 
// Sono possibili altre semplificazioni per ridurre ulteriormente la complessità.
