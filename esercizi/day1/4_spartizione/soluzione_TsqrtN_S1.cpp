#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int G, P; in >> G >> P;

  // L'algoritmo è una simulazione della spartizione.
  
  // Numero di gemme date a Totò. Inizialmente Totò non ne ha nessuna.
  int gemme_toto = 0;

  // Numero di gemme da dare a Totò in questa iterazione.
  int gemme_da_dare_a_toto = 1;
  
  // Finchè ci sono gemme andiamo avanti con la simulazione.
  while (G > 0) {
    // Le gemme potrebbero non essere sufficienti: eventualmente Totò prende tutte le rimanenti.
    gemme_toto += min(G, gemme_da_dare_a_toto);

    // Togliamo le gemme dell'iterazione. Anche se andiamo sotto zero non è un problema.
    // Gli altri si prendono complessivamente `P-1` gemme.
    G -= gemme_da_dare_a_toto + (P - 1);

    // All'iterazione successiva Totò prende una gemma in più.
    ++gemme_da_dare_a_toto;
  }

  out << gemme_toto;

  // Si può dimostrare che questo algoritmo è un Θ(sqrt(G + P²) - P) dal punto di vista della complessità temporale.

  in.close(); out.close();
}
