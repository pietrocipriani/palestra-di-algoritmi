#include <bits/stdc++.h>
using namespace std;
#define MAX_GRADAZIONE 99

// Relativamente alla soluzione precedente.
// È possibile osservare che, tralasciando la questione della `minima_gradazione` che ci impone dei vincoli sulle scelte, per il resto otteniamo sostanzialmente una sequenza di Fibonacci.
// L'algoritmo 0_soluzione.cpp è quindi un algoritmo esponenziale. (phi^n se a qualcuno può interessare).
//
// Facciamo un esempio: arrivano vini con queste gradazioni:
// 5 7 10 9 [...]
// Prendiamo il 5 e poi il 10: chiamiamo prendo_non_prendo([...], 10). Dove [...] sarebbe 4, tuttavia così è più chiaro che ci rimangono da analizzare tutti i vini [...].
// Possiamo anche non prendere il 5, non prendere il 7 e prendere il 10: chiamiamo prendo_non_prendo([...], 10).
//
// Si può dunque osservare che `prendo_non_prendo` viene chiamata più volte con gli STESSI PARAMETRI, ai quali la funzione risponde alla stessa identica maniera.
// Perchè non memorizzare i risultati per poi riutilizzarli immediatamente senza ricalcolarli?
//
// È possibile fare degli esperimenti per verificare che questo fenomeno di "ripetizione delle chiamate" è parecchio presente.

// Vettore dei vini. Ci interessa solo la gradazione (`int`).
vector<int> vini;

// Creo una "cache": un'area di memoria dove poter memorizzare i risultati delle chiamate a `prendo_non_prendo`.
// `prendo_non_prendo` ha 2 parametri e non legge nessuna variabile esterna che può cambiare valore.
// Questo significa che i valori di `prendo_non_prendo` dipendono solo ed esclusivamente dai due parametri.
// Quindi possiamo creare una `cache` bidimensionale, dove ogni dimensione va a spaziare i possibili valori del parametro corrispondente.
//
// ATTENZIONE che in certi casi i parametri potrebbero essere "rindondanti", ossia almeno uno può essere in realtà ricavato dagli altri: in questi casi è possibile ridurre la dimensione.
// Se possibile è meglio ridurre la dimensione: questa tecnica è MOLTO invasiva in termini di memoria.
vector<vector<int>> cache;

// Funzione che prova a prendere e a non prendere uno stesso vino, per confrontare con quale scelta è possibile ottenere un risultato migliore.
int prendo_non_prendo(int i = 0, int minima_gradazione = 0) {
  // Come prima, se sono finiti i vini allora non ne possiamo prendere nessuno.
  if (i >= vini.size()) return 0;
  // Se abbiamo già un valore in `cache` allora è già stato calcolato: ci basta andare a restituire quel valore.
  if (cache.at(i).at(minima_gradazione) >= 0) return cache.at(i).at(minima_gradazione);
  // Altrimenti proseguo con l'algoritmo "standard".

  int vino = vini.at(i);

  int result;
  if (vino < minima_gradazione) result = prendo_non_prendo(i + 1, minima_gradazione);
  else result = max(
    prendo_non_prendo(i + 1, minima_gradazione),
    prendo_non_prendo(i + 2, vino) + 1
  );

  // Salvo il valore trovato per le successive chiamate.
  return cache.at(i).at(minima_gradazione) = result;
}

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N; in >> N;
  vini.resize(N);

  // Inizializzo la cache a -1! È Importante che sia un valore al di fuori dei possibili risultati della funzione `prendo_non_prendo`.
  // In questo caso andava bene anche 0. Tanto viene restituito solo ed esclusivamente quando non ci sono più vini.
  // Questa chiamata può essere parecchio impegnativa se la cache è grande.
  // Vedremo più avanti altri modi per "generare a chiamata" la cache. (Hash table per chi è curioso).
  cache.resize(N, vector<int>(MAX_GRADAZIONE + 1, -1));

  for (int& vino : vini) in >> vino;

  out << prendo_non_prendo();

  in.close(); out.close();
}
