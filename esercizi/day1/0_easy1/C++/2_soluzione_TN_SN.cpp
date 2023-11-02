#include <bits/stdc++.h>
using namespace std;

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

  // L'idea di questa ottimizzazione è iterare gli elementi del `vector` per andare ad aggiornare pian piano il massimo.
  // Inizialmente partiamo da un vettore di 1 elemento e pian piano lo ingrandiamo sempre di più, aggiungendo gli altri elementi.
  // Inizialmente `massimo` è pari al primo elemento: questo è effettivamente il massimo del vettore da 1 elemento.
  // Ad ogni iterazione vediamo se il nuovo elemento è più grande di `massimo` ed eventualmente lo aggiorniamo.
  // Se il nuovo elemento è più grande di `massimo` allora è anche più grande di ogni altro elemento del vettore che stiamo costruendo.
  // Infatti si ha: altri_elementi <= massimo_precedente < nuovo_elemento. Ossia il nuovo elemento è più grande di tutti gli altri elementi.
  // Se il nuovo elemento non è più grande di `massimo` allora possiamo lasciare tranquillamente `massimo` come valore massimo.
  // Infatti si ha: massimo_precedente >= altri_elementi e massimo_precedente >= nuovo_elemento, ossia massimo_precedente >= tutti_gli_elementi_attualmente_considerati.
  int massimo = Ss.at(0);

  // partiamo dal secondo elemento. Il vettore di dimensione 1 lo abbiamo già analizzato.
  for (int i = 1; i < N; ++i) {
    // Aggiorno il massimo in modo che prenda il massimo fra `massimo` e il nuovo elemento.
    massimo = max(massimo, Ss.at(i));
  }

  // A questo punto `massimo` contiene il massimo del vettore costituito dai primi `N` elementi. Che è proprio l'intero vettore! Abbiamo il massimo del vettore.
  out << massimo;

  // Osservazioni sulla complessità dell'algoritmo.
  //
  // Dal punto di vista del "tempo":
  //   Il loop per l'aggiornamento del massimo ci costa a·N
  //   Il loop di lettura ci costa c·N.
  //   Vi è un uteriore costo `d` dovuto alle operazioni che eseguiamo una sola volta, fuori dai loop.
  //   La complessità è data da: d + c·N + a·N.
  //   La complessità complessiva è dunque Θ(N).
  //
  // Dal punto di vista dello "spazio":
  //   L'utilizzo dello spazio lo possiamo stimare con Θ(N).

  in.close(); out.close();
}
