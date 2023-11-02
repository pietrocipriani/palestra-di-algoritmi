#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di elementi: parametro del problema.
  int N;
  in >> N;

  // Creiamo il vettore che conterrà tutti gli S.
  // Dal momento che sappiamo già quanti elementi vogliamo memorizzare, lo creiamo di già della giusta dimensione.
  // Così non perdiamo tempo a copiare elementi durante il ridimensionamento (vedere la teoria sui `vector`).
  vector<int> Ss(N);

  // Modo standard di ripetere un blocco di istruzioni N volte.
  for (int i = 0; i < N; ++i) {
    // Leggiamo il prossimo valore e lo inseriamo nel `vector` nella posizione corrispondente.
    in >> Ss[i];
  }

  // `foreach`: costrutto di C++ che permette di iterare (accedere a tutti gli elementi uno per volta) sulle collezioni di elementi.
  // Python:
  // ```
  // for element in list:
  //    pass
  // ```
  // C++:
  // ```
  // for (type& element : list) {
  // }
  // ```
  loop1: for (int S : Ss) {
    // Il massimo è definito come quel valore >= di tutti gli altri valori.
    
    // Vogliamo trovare se esiste un valore più grande di `S` per dimostrare che `S` non è il massimo.
    // Fino a prova contraria `S` è il massimo.
    bool maggiore = true;

    // Iteriamo su tutti gli altri elementi.
    loop2: for (int altro_valore : Ss) {
      // Se `S` è minore anche di un solo `altro_valore`, allora sicuramente non è il massimo.
      if (S < altro_valore) {
        maggiore = false;
        break;
      }
    }

    // Se `S` è maggiore di tutti gli altri valori allora è il massimo.
    // Non per forza è unico: ci possono essere più valori uguali.
    // Tuttavia possiamo terminare: se sono uguali il massimo è comunque `S`.
    if (maggiore) {
      // Stampo il valore di massimo individuato.
      out << S;
      // Termino il `loop1`: il programma prosegue fuori_da_loop1.
      break;
    }
  }
  fuori_da_loop1:

  // Osservazioni sulla complessità dell'algoritmo.
  //
  // Dal punto di vista del "tempo":
  //   Abbiamo 2 cicli uno dentro l'altro:
  //     Nel caso pessimo (il massimo si trova alla fine), usciamo dal `loop1` dopo N iterazioni di `loop1`.
  //       Nel mentre effettuiamo delle operazioni che ci costano `a`: una COSTANTE di tempo.
  //     Ad ogni iterazione di `loop1`, scorriamo tutti e N gli elementi del vettore (N iterazioni di `loop2` per ogni iterazione di `loop1`).
  //       Ogni iterazione di `loop2` ci costa `b`: un'altra COSTANTE di tempo.
  //     Complessivamente il doppio loop ci costa N·(a + b·N).
  //   Il loop di lettura ci costa c·N.
  //   Vi è un uteriore costo `d` dovuto alle operazioni che eseguiamo una sola volta, fuori dai loop.
  //   La complessità è data da: d + c·N + N·(a + b·N).
  //   Facciamo finta che N diventi MOOOOOLTO grande: nelle somme si possono trascurare le costanti rispetto a N.
  //   Risulta dunque che la complessità è all'incirca: b·N².
  //   Dal momento che è difficile quantificare il costo `b`, solitamente è possibile ignorare le costanti moltiplicative.
  //   La complessità è dunque all'incirca N².
  //   il fatto che si stia parlando di una approssimazione (stima) la indichiamo con la notazione `Θ(N²)`.
  //   ATTENZIONE: abbiamo valutato il caso PESSIMO... in media come si comporta?
  //   Vedremo che questo algoritmo si può implementare in Θ(N): tale algoritmo è MOLTO meglio.
  //   Ci permette di gestire un milione di elementi con la stessa fatica con cui questo algoritmo ne gestisce 1000.
  //
  // Dal punto di vista dello "spazio":
  //   Abbiamo un po' di variabili "singole" che occupano uno spazio COSTANTE `a` (costante al variare di N).
  //   Abbiamo un vettore di `N` elementi di dimensione `b`: occupa b·N.
  //   L'utilizzo dello spazio lo possiamo stimare con Θ(N).

  in.close(); out.close();
}
