#include <bits/stdc++.h>
using namespace std;
#define MAX_GRADAZIONE 99

// Relativamente alla soluzione precedente.
// In alcuni casi (non questo problema), è possibile osservare come, al termine delle chiamate ricorsive, sia stato compilata sostanzialmente TUTTA la cache.
// Se le chiamate ricorsive sono DENSE, allora può aver senso valutare di passare alla programmazione dinamica.
// Altrimenti le chiamate si dicono SPARSE: in questo caso, non abbiamo troppo controllo su `minima_gradazione` e pertanto potenzialmente può saltare parecchio in avanti.
//
// La programmazione dinamica riprende esattamente il principio della memoization: non ripetere le stesse valutazioni,
// tuttavia ha un approccio completamente differente: compila la cache per poi restituire la cella corrispondente all'intero problema.
// ATTENZIONE: non sempre è possibile utilizzare la programmazione dinamica: dipende molto dalla relazione di dipendenza fra le celle!
//
// La programmazione dinamica, in quanto iterativa, con compilazioni DENSE è meglio della memoization in quanto ricorsiva.

// Vettore dei vini. Ci interessa solo la gradazione (`int`).
vector<int> vini;

// Cache identica alla soluzione con memoization.
vector<vector<int>> cache;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N; in >> N;
  vini.resize(N);

  // Non abbiamo grosso interesse nell'inizializzazione, tanto andremo a ricompilare tutto.
  // Per N + 2 vedasi dopo.
  cache.resize(N + 2, vector<int>(MAX_GRADAZIONE + 1, 0));

  for (int& vino : vini) in >> vino;

  // Dobbiamo accedere alle celle corrispondenti ai vini successivi (i+1 e i+2). Abbiamo la necessità che siano già state compilate.
  // Iteriamo quindi a ritroso.
  for (int i = N - 1; i >= 0; --i) {
    // Dobbiamo accedere a `minima_gradazione` o `vino`, quindi si va a rialzo. Tuttavia non ci capiterà mai di riutilizzare i valori su uno stesso vino `i`, ma sono sui successivi.
    // Il fatto che le celle siano già state compilate ci è garantito dal ciclo esterno. Non ci sono particolari richieste per come iterare le gradazioni.
    // In realtà non abbiamo nessuna garanzia che siano necessari TUTTI i valori di gradazione, quindi potenzialmente facciamo tanto lavoro per nulla: in QUESTO problema è probabilmente meglio la memoization.
    for (int minima_gradazione = 0; minima_gradazione <= MAX_GRADAZIONE; ++minima_gradazione) {
      // È letteralmente lo stesso codice della soluzione precedente.
      
      // Non possiamo gestire il caso base con i >= N dato che partiamo da i = N-1.
      // Tuttavia proprio con i = N-1 abbiamo il problema che i+1 = N e i+2 = N+1.
      // Quindi dobbiamo allargare la tabella in modo da comprendere anche N e N+1.
      // prendo_non_prendo(N, ?) = prendo_non_prendo(N+1, ?) dava sempre 0, quindi possiamo tranquillamente inizializzare a 0 l'intera cache.
      // Così le righe corrispondenti a N e N+1 saranno già correttamente inizializzate e non dobbiamo iterarle.
      // Altrimenti, nel caso fosse più complicato stabilire il valore, era possibile allargare i valori di `i` partendo da N+1 e gestire il caso base con un if qui sotto.
      
      int vino = vini.at(i);
    
      int result;
      if (vino < minima_gradazione) result = cache.at(i + 1).at(minima_gradazione); // prendo_non_prendo(i + 1, minima_gradazione)
      else result = max(
        cache.at(i + 1).at(minima_gradazione),  // prendo_non_prendo(i + 1, minima_gradazione)
        cache.at(i + 2).at(vino) + 1            // prendo_non_prendo(i + 2, vino)
      );
      cache.at(i).at(minima_gradazione) = result; // valore di prendo_non_prendo(i, minima_gradazione)
    }
  }

  // Cella corrispondente a `prendo_non_prendo(0, 0)`.
  out << cache.at(0).at(0);

  in.close(); out.close();
}
