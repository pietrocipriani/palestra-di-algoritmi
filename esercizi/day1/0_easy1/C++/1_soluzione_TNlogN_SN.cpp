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

  // modo standard per ordinare un `vector` in ordine crescente.
  sort(Ss.begin(), Ss.end());

  // Una volta ordinato il vettore sappiamo che il massimo si troverà all'ultimo posto.
  out << Ss.at(N-1);

  // Abbiamo risparmiato sicuramente molte linee di codice: la complessità è rimasta invariata?
  // Osservazioni sulla complessità dell'algoritmo.
  //
  // Dal punto di vista del "tempo":
  //   L'algoritmo `sort` della STDC++ ha un caso pessimo di Θ(N·logN). Ossia abbiamo una funzione a·N·logN + qualcosa di trascurabile.
  //   `logN` è una funzione matematica che molti di voi probabilmente non conoscono. Ciò che ci interessa è che logN cresce MOLTO più lentamente di N.
  //   Il loop di lettura ci costa c·N.
  //   Vi è un uteriore costo `d` dovuto alle operazioni che eseguiamo una sola volta, fuori dai loop.
  //   La complessità è data da: d + c·N + a·N·logN.
  //   Il termine più "grosso" rimane comunque a·N·logN.
  //   La complessità complessiva è dunque Θ(N·logN).
  //   Anche in questo caso l'algoritmo Θ(N) è meglio (tuttavia questo algoritmo è molto meglio del precedente).
  //   L'algoritmo implementato dalla STDC++ è chiamato Introsort ed è una combinazione di 3 algoritmi differenti, in modo da selezionare le caratteristiche migliori fra questi:
  //     In particolare impiega anche un algoritmo Θ(N²) che tuttavia è estremamente veloce con N molto piccolo.
  //
  // Dal punto di vista dello "spazio":
  //   L'utilizzo dello spazio lo possiamo stimare con Θ(N).

  in.close(); out.close();
}
