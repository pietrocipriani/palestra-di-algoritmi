#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di macchine.
  int N; in >> N;

  // Numero di sorpassi.
  int M; in >> M;

  // Variabile che contiene l'auto al primo posto pian piano che avvengono i sorpassi.
  int primo; in >> primo;

  for (int i = 1; i < N; ++i) {
    // Non ci interessa nulla di tutti gli altri, tuttavia dobbiamo liberare "input.txt" in modo da leggere i sorpassi.
    int ignore; in >> ignore;
  }

  // Leggiamo tutti i sorpassi.
  for (int i = 0; i < M; ++i) {
    int sorpassante, sorpassato; in >> sorpassante >> sorpassato;

    // Se è stato sorpassato il primo allora il sorpassante diventa il primo. Altrimenti non ci interessa.
    if (sorpassato == primo) primo = sorpassante;
  }

  out << primo;

  in.close(); out.close();
}
