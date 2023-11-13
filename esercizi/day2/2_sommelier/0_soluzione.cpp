#include <bits/stdc++.h>
using namespace std;

// Vettore dei vini. Ci interessa solo la gradazione (`int`).
vector<int> vini;

// Funzione che prova a prendere e a non prendere uno stesso vino, per confrontare con quale scelta è possibile ottenere un risultato migliore.
// Restituisce il valore della lunghezza massima fino a questo momento.
// Si poteva fare anche a ritroso, ma così era più intuitivo, dato che è letteralmente una simulazione delle scelte del sommelier.
// Con `i` indico il vino in arrivo. Con `minima_gradazione` indico la minima gradazione che deve avere il vino per poter essere preso. Corriponde alla gradazione dell'ultimo vino preso.
int prendo_non_prendo(int i = 0, int minima_gradazione = 0) {
  // Sono finiti i vini, non ne possiamo prendere altri: "al massimo ne possiamo prendere 0".
  if (i >= vini.size()) return 0;

  int vino = vini.at(i);

  // Se la gradazione del vino è troppo bassa allora non ci poniamo nemmeno il problema: non possiamo prenderlo.
  if (vino < minima_gradazione) return prendo_non_prendo(i + 1, minima_gradazione);

  // Altrimenti proviamo a vedere quale scelta ci permette di ottenere un risultato migliore.
  return max(
    // Non prendo il vino: passo al successivo e la minima gradazione rimane sempre quella.
    prendo_non_prendo(i + 1, minima_gradazione),
    // Prendo il vino: salto il vino successivo e i prossimi vini dovranno avere gradazione >= di questo vino. +1 perchè ho preso questo `vino`.
    prendo_non_prendo(i + 2, vino) + 1
  );
}

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N; in >> N;
  vini.resize(N);

  // Leggiamo tutti i vini.
  for (int& vino : vini) in >> vino;

  // Provo tutte le combinazioni e prendo la lunghezza massima.
  out << prendo_non_prendo();

  in.close(); out.close();
}
