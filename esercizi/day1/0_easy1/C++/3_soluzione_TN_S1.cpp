#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di elementi: parametro del problema.
  int N;
  in >> N;

  // Nell'algoritmo precedente è possibile osservare come gli elementi vengano letti dal vettore una sola volta e in maniera sequenziale.
  // È quindi possibile evitare di memorizzarli, consumandoli pian piano che li leggiamo.

  int massimo;
  in >> massimo; // massimo = Ss.at(0);

  // partiamo dal secondo elemento. Il vettore di dimensione 1 lo abbiamo già analizzato.
  for (int i = 1; i < N; ++i) {
    int S;
    in >> S; // Ss.at(i);

    // Aggiorno il massimo in modo che prenda il massimo fra `massimo` e il nuovo elemento.
    massimo = max(massimo, S);
  }

  // A questo punto `massimo` contiene il massimo del vettore costituito dai primi `N` elementi. Che è proprio l'intero vettore! Abbiamo il massimo del vettore.
  out << massimo;

  // Questo è l'algoritmo "standard" per la ricerca di un massimo (o minimo).

  // Osservazioni sulla complessità dell'algoritmo.
  //
  // Dal punto di vista del "tempo":
  //   Il loop per l'aggiornamento del massimo ci costa a·N
  //   Vi è un uteriore costo `d` dovuto alle operazioni che eseguiamo una sola volta, fuori dai loop.
  //   La complessità è data da: d + a·N.
  //   La complessità complessiva è dunque Θ(N).
  //   Probabilmente è leggermente più veloce dell'algoritmo precedente... tuttavia va considerato che la `a` non è la stessa `a` dell'altro algoritmo, e che le operazioni di IO sono abbastanza pesanti.
  //
  // Dal punto di vista dello "spazio":
  //   L'utilizzo dello spazio lo possiamo stimare con Θ(1).
  //   Lo spazio occupato non dipende dall'input!

  in.close(); out.close();
}
