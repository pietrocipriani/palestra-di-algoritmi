#include <bits/stdc++.h>
using namespace std;

// Funzione richiesta dal problema, si poteva fare tutto nel main.
// `D` rigorosamente passato per RIFERIMENTO!
int interroga(int K, vector<int>& D) {
  // L'idea è quella di prendere un blocco di K domande consecutive dal punto di vista della complessità.
  // Facciamo infatti finta di scartare una domanda fra quelle con complessità in mezzo alla complessità minima e massima delle domande selezionate.
  // La differenza iniziale è data da `max - min`. Se rimpiazziamo la domanda `min` (sì, rigorosamente domande sempre più difficili :) ) con quella scartata
  // si ottiene una differenza `max - min2` che però è minore o uguale a quella precedente dato che `min2` è >= di `min`.
  // Sicuramente anche la domanda scartata non può modificare il `max` o il `min` dato che per ipotesi era compresa proprio fra questi due.
  // 
  // L'idea è che quindi abbia senso andare ad ordinare gli elementi del vettore e fa scorrere una "finestra" di dimensione `K` (la finestra delle "domande selezionate")
  // per prendere quella con la differenza minore fra gli estremi.

  // Ordiniamo gli elementi del vettore.
  sort(D.begin(), D.end());

  // Inizializziamo il minimo in modo che sia MOOOLTO grande (il valore più grande rappresentabile da `int`).
  int minimo = std::numeric_limits<int>::max();

  // facciamo scorrere la finestra in modo che parta da `first` e termini in `first + K - 1` (inclusivo) ossia abbia K elementi.
  // Ovviamente l'ultimo elemento della finestra deve stare all'interno del vettore.
  for (int first = 0; first + K - 1 < D.size(); ++first) {
    // La domanda più facile è `D[first]`, quella più difficile è `D[first + K - 1]`: il vettore è ordinato!
    // Aggiorniamo il minimo con il solito procedimento del minimo parziale.
    minimo = min(minimo, D[first + K - 1] - D[first]);
  }

  // Restituiamo il valore.
  return minimo;
}

// Ho riadattato il codice fornito da olinfo che era scritto in C e utilizzava dei concetti che preferisco non introdurre, come array e puntatori.
// Sono degli strumenti che vengono impiegati relativamente poco in codici "moderni" e di qui esistono alternative valide ad "alto livello".
//
// Se in qualche competizione/esercizio vi venisse chiesto di implementare una funzione dove viene passato un array, potete fare:
// `vector<T> vettore(array, array+N);`
// per convertire l'array in un vettore. L'operazione però è O(N).

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");
  int N, K;

  in >> N >> K;

  // Vettore contenente le difficoltà dei vari quesiti.
  vector<int> D(N);
  // Rigorosamente per RIFERIMENTO: lo vogliamo modificare.
  for (int& d : D) in >> d;

  out << interroga(K, D);
  
  in.close(); out.close();
}
