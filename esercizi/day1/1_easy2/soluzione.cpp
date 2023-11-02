#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di elementi: parametro del problema.
  int N;
  in >> N;

  // Riutilizziamo l'algoritmo di `easy1`. Semplicemente andremo a generare gli elementi pian piano effettuando la somma.
  // La gestione pari/dispari la effettuiamo con un if.

  // Non inizializziamo più `massimo` con la prima somma: non siamo sicuri sia pari.
  // Inizializziamo `massimo` a -1. È un valore sicuramente minore del massimo effettivo ed è il valore di default nel caso non vi siano somme pari.
  int massimo = -1;

  // partiamo dal primo elemento!
  for (int i = 0; i < N; ++i) {
    // I due termini della somma
    int a, b;
    in >> a >> b;

    // "generiamo" l'elemento che ci interessa... che dobbiamo massimizzare.
    int S = a + b;

    // `%` ritorna il resto della divisione. Se il resto della divisione per 2 è 0, allora `S` è divisibile per 2 (ossia è pari).
    // Se `S` è dispari lo ignoriamo.
    if (S % 2 == 0) {
      massimo = max(massimo, S);
    }
  }

  out << massimo;

  // L'algoritmo ha complessità temporale Θ(N).
  // L'algoritmo ha complessità spaziale Θ(1).

  in.close(); out.close();
}
