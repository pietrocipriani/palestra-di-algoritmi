#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N; in >> N;

  // Massima differenza incontrata fino a questo momento.
  // Il problema non specifica quale debba essere l'output nel caso di N=1 (nessuna differenza).
  // La differenza (in valore assoluto) è >= 0, quindi possiamo tranquillamente inizializzare a 0.
  int max_diff = 0;

  // valore precedente. Per calcolare la differenza.
  int prev; in >> prev;

  // leggiamo N-1 elementi (il primo è già stato letto.)
  for (int i = 1; i < N; ++i) {
    // nuovo valore.
    int num; in >> num;

    // differenza in valore assoluto.
    int diff = abs(prev - num);

    // aggiorniamo la differenza se necessario.
    max_diff = max(max_diff, diff);

    // il valore attuale diventa il prossimo "valore precedente".
    prev = num;
  }  
  
  out << max_diff;

  in.close(); out.close();
}
