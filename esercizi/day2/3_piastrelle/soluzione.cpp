#include <bits/stdc++.h>
using namespace std;

// Non ci interessa più N. Lavoriamo sulla dimensione di `str`.
// Una piastrella singola occupa 3 caratteri, una doppia ne occupa 6. Complessivamente tutte le soluzioni hanno lo stesso numero di caratteri (!!!).
void backtracking(string& str, int caratteri_usati = 0) {
  // Se abbiamo finito i caratteri allora stampiamo la stringa ottenuta.
  if (caratteri_usati >= str.size()) {
    // PS: '\n' è "meglio" di `endl`.
    // PS: la stampa ci costa O(N)!
    cout << str << '\n';
    return;
  }
  // Rimpiazziamo i 3 caratteri a partire da `caratteri_usati` con il pattern della piastrella singola.
  str.replace(caratteri_usati, 3, "[O]");
  // Proseguiamo...
  backtracking(str, caratteri_usati + 3);

  // Se possiamo inserire una piastrella doppia...
  if (caratteri_usati + 6 <= str.size()) {
    // Rimpiazziamo i 6 caratteri a partire da `caratteri_usati` con il pattern della piastrella doppia.
    str.replace(caratteri_usati, 6, "[OOOO]");
    // Proseguiamo...
    backtracking(str, caratteri_usati + 6);
  }
}

int main() {
  // Dobbiamo scrivere in una funzione: ci conviene impiegare `cout`, altrimenti dobbiamo fare `in` e `out` globali.
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N; cin >> N;

  // Creiamo una `string` (sequenza di caratteri) di dimensione 3 * N ed inizializzata con un valore arbitrario.
  // Sono 3 caratteri per ogni "unità":
  // - piastrella singola: [O] = 3 caratteri
  // - piastrella doppia: [OOOO] = 6 caratteri
  string str(3 * N, ' ');

  // Andiamo a valutare tutte le possibilità.
  backtracking(str);
}
