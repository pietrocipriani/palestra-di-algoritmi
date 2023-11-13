#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N, M; in >> N >> M;

  // L'idea è che:
  // f(i) = f(i-1) - f(i-2) + f(i-1) - f(i-3) + ... + f(i-1) - f(0) = (i-1)·f(i-1) - "somma degli f(j) con j fra 0 e i-2".
  // Possiamo tranquillamente andare a memorizzare le somme parziali: sommiamo un termine alla volta man mano che li calcoliamo.
  // Possiamo inoltre memorizzare il termine precedente f(n).

  // Somma mod M. Inizieremo con i = 2, quindi sommiamo solo f(i-2 = 0): f(0) = -1 = M-1 mod M
  int sum = M - 1;
  
  // Partiamo da 2, f(i-1 = 1) = 0
  int prev = 0;

  for (int i = 2; i <= N; ++i) {
    // Secondo le proprietà fornite nel testo del problema:
    // ((i - 1) * prev) mod M = {[(i - 1) mod M] * (prev mod M)} mod M
    // `sum` e `prev` li memorizziamo di già mod M.
    // La differenza restituisce un numero compreso fra -M e M. Con il +M otteniamo un numero compreso fra 0 e 2M. Con %M otteniamo un numero fra 0 e M.
    // Al contrario di linguaggi come Python, in C++ l'operatore % restituisce un valore negativo quando il dividendo è negativo.
    int next = ((((i - 1) % M) * prev) % M - sum + M) % M;
    // Aggiorniamo la somma aggiungendo f(i-1)
    sum += prev;
    // Salviamo la somma mod M per evitare overflow e anche perchè è più comoda mod M.
    sum %= M;
    // Il prossimo f(i'-1) è proprio f(i).
    prev = next;
  }

  // `prev` contiene il valore calcolato nell'ultima iterazione.
  out << prev;

  in.close(); out.close();
}
