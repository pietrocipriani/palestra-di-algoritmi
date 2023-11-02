#include <bits/stdc++.h>
using namespace std;

// DISCLAIMER: questa soluzione è qui solo per completezza.

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di elementi: parametro del problema.
  int N;
  in >> N;

  // Creiamo il vettore che conterrà tutti gli S.
  vector<int> Ss(N);

  for (int& S : Ss) {
    // Leggiamo il prossimo valore e lo inseriamo nel `vector` nella posizione corrispondente.
    in >> S;
  }

  // Utilizziamo la funzione per il massimo della libreria `algorithm` inclusa con `bits/stdc++`
  // Questa soluzione non è didattica! È meglio ragionare sul come implementare la funzione di massimo.
  // `begin()` e `end()` sono degli _iteratori_. Puntano a degli elementi del vettore e possono essere incrementati e decrementati per scorrere il vettore.
  // `max_element` a sua volta ci restituisce un iteratore.
  // Per accedere all'elemento puntato dall'iteratore è possibile usare l'operatore unario `*`.
  // PS per chi conosce i puntatori: gli iteratori NON sono per forza puntatori (in alcuni casi possono esserlo). Sono uno strumento più potente. Tuttavia sono stati implementati in modo da assomigliare alla sintassi dei puntatori.
  int massimo = *max_element(Ss.begin(), Ss.end());

  // In alternativa, per evitare il vettore, è possibile utilizzare `istream_iterator`. Ossia un iteratore che va a leggere direttamente da un `istream` (`in` nel nostro esempio è un `ifstream` che però è una specializzazione di `istream` per i file).
  // int massimo = *max_element(istream_iterator<int>(in), istream_iterator<int>());

  out << massimo;


  in.close(); out.close();
}
