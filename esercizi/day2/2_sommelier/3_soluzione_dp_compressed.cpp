#include <bits/stdc++.h>
using namespace std;
#define MAX_GRADAZIONE 99

// Soluzione solo per chi è interessato. Eventualmente ottimizzazioni del genere verranno valutate più avanti, quando sarà veramente necessario utilizzarle per risolvere problemi.
//
// Relativamente alla soluzione precedente:
// Uno dei vantaggi della programmazione dinamica, rispetto alla memoization, è la possibilità di avere il "controllo" sulla compilazione della tabella.
// Nella memoization, infatti, la funzione ricorsiva può saltare "da una parte all'altra".
// Ciò ci consente, in alcuni casi, di effettuare delle ottimizzazioni dal punto di vista della memoria.

vector<int> vini;

vector<vector<int>> cache;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N; in >> N;
  vini.resize(N);

  // Non abbiamo grosso interesse nell'inizializzazione, tanto andremo a ricompilare tutto.
  // Per ogni `i` accediamo solo a `i+1` e `i+2`... non ha senso memorizzare tutte le altre righe: non le andremo a leggere mai più.
  // Potenzialmente in altri problemi saranno necessarie più righe (almeno quella di `i`), in questo è possibile sovrascrivere "in place" senza perdere informazioni.
  // 
  // ATTENZIONE: se si decidesse di usare 3 righe: ad ogni iterazione sarà necessario fare in modo che la riga corrispondente a `i` diventi `i+1` nell'iterazione successiva e così via:
  // Fare una cosa del genere è impegnativo dato che richiede di copiare cache[1] in cache[2] e cache[0] in cache[1]:
  // ```
  // cache[2] = cache[1];
  // cache[1] = cache[0];
  // ```
  // Si può usare `std::move`:
  // ```
  // cache[2] = std::move(cache[1]);
  // cache[1] = std::move(cache[0]);
  // ```
  // In questo modo cache[2] si appropria dei dati in cache[1] e cache[1] rimane in uno stato "non specificato".
  // Tuttavia nell'istruzione successiva cache[1] si appropria dei dati di cache[0] e cache[0] rimane "non specificato".
  // Tuttavia di cache[0] non ci interessa granchè: i suoi dati vengono riscritti all'iterazione successiva.
  // Con `std::move` non avvengono copie!
  //
  // Inizializziamo a 0 sempre per i casi base (i=N e i=N+1).
  cache.resize(2, vector<int>(MAX_GRADAZIONE + 1, 0));

  for (int& vino : vini) in >> vino;
  
  // Iteriamo a ritroso per le stesse questioni della soluzione precedente.
  for (int i = N - 1; i >= 0; --i) {
    // ATTENZIONE: con la scusa che sovrascriviamo "in place", non possiamo modificare prima i valori di gradazione più alta!
    // Perchè altrimenti non sono più disponibili per le gradazioni più basse (si va a rialzo).
    // Dobbiamo dunque iterare per forza da 0 a MAX_GRADAZIONE.
    for (int minima_gradazione = 0; minima_gradazione <= MAX_GRADAZIONE; ++minima_gradazione) {
      int vino = vini.at(i);
    
      int result;
      if (vino < minima_gradazione) result = cache.at(0).at(minima_gradazione); // prendo_non_prendo(i + 1, minima_gradazione)
      else result = max(
        cache.at(0).at(minima_gradazione),  // prendo_non_prendo(i + 1, minima_gradazione)
        cache.at(1).at(vino) + 1            // prendo_non_prendo(i + 2, vino)
      );
      // `i+1` -> `i+2`
      cache.at(1).at(minima_gradazione) = cache.at(0).at(minima_gradazione);
      // `i` -> `i+1`
      cache.at(0).at(minima_gradazione) = result; // valore di prendo_non_prendo(i, minima_gradazione)
    }
  }

  // Cella corrispondente a `prendo_non_prendo(0, 0)`.
  out << cache.at(0).at(0);

  in.close(); out.close();
}
