#include <bits/stdc++.h>
using namespace std;

// Questo in C/C++ è detto PROTOTIPO.
// Il compilatore compila un file .cpp alla volta e in maniera sequenziale.
// Questo prototipo ci serve per dire al compilatore che "esiste una funzione void Vernicia(int, int)" da qualche parte. Tuttavia non la definiamo.
void Vernicia(int indice, int colore);

// Funzione richiesta dal grader che passa un array di colori.
void Diversifica(int N, int colore[]) {
  // Usiamo una mappa che associa ad ogni colore (-1) il numero di piastrelle con quel colore.
  vector<int> colori_utilizzati(N, 0);

  // Scorriamo tutte le piastrelle e incrementiamo il conteggio del colore relativo.
  for (int i = 0; i < N; ++i) {
    // Possiamo accedere un elemento dell'array con la sintassi colore[i], con lo stesso significato di `vettore.at(i)`.
    // I colori sono indicizzati da 1, quindi dobbiamo usare il -1 per riportare i colori da [1, N] a [0, N)
    ++colori_utilizzati.at(colore[i] - 1);
  }

  // Indice che va in cerca del primo colore disponibile.
  int colore_disponibile = 1;

  // Scorriamo tutte le piastrelle per stabilire se vanno ricolorate o meno.
  for (int i = 0; i < N; ++i) {
    // Se c'è più di una piastrella con questo colore allora la ricoloriamo.
    if (colori_utilizzati.at(colore[i] - 1) > 1) {
      // Cerchiamo il primo colore che non è stato mai usato.
      while(colori_utilizzati.at(colore_disponibile - 1) != 0) ++colore_disponibile;
      // Riveniciamo la piastrella di quel colore.
      Vernicia(i, colore_disponibile);

      // Abbiamo utilizzato il `colore_disponibile`.
      // Potevamo risparmiarci questa operazione e limitarci a incrementare `colore_disponibile` in modo che non possa più riselezionare questo colore.
      // Tuttavia mi sembra più chiaro lo scopo in questa maniera.
      ++colori_utilizzati.at(colore_disponibile - 1);

      // Non stiamo più utilizzando `colore[i]`.
      // Questa operazione è IMPORTANTE: se ci sono 2 piastrelle con lo stesso colore e riverniciamo la prima, la seconda DEVE rimanere dello stesso colore... altrimenti esauriamo i colori.
      --colori_utilizzati.at(colore[i] - 1);
    } 
  }
}
