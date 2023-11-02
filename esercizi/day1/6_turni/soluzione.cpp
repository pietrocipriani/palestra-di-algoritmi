#include <bits/stdc++.h>
using namespace std;

// Struttura contenente il tempo di inizio e di fine dei vari intervalli di tempo.
struct Intervallo {
  int inizio, fine;
};

// Come nell'esercizio precedente. Serve per `sort`.
// Questa è la definizione di un OPERATORE: ci permette di scrivere
// ```
// Intervallo i1, i2;
// ...
// if (i1 < i2) {
//   ... 
// }
// ```
//
// ATTENZIONE: `std::sort`, di default, ordina con `std::less`. Ossia vuole proprio l'operatore `<`! Non è la stessa cosa usare il `>`.
bool operator<(const Intervallo& i1, const Intervallo& i2) {
  // In caso di pareggio si potrebbe valutare la `fine`. Tuttavia per il nostro algoritmo non cambia nulla.
  return i1.inizio < i2.inizio;
}

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");
  
  // Numero di giorni
  int K; in >> K;

  // Numero di persone
  int N; in >> N;

  // Come detto nella teoria dei `vector` è meglio fornire di già la dimensione.
  vector<Intervallo> intervalli(N);

  // Leggiamo tutti gli intervalli.
  for (Intervallo& intervallo : intervalli) {
    in >> intervallo.inizio >> intervallo.fine;
  }

  // Ordiniamo gli intervalli in modo da avere quelli che iniziano prima per primi.
  // È una proprietà che verrà sfruttata dal resto dell'algoritmo.
  sort(intervalli.begin(), intervalli.end());

  // Il primo tempo non ancora coperto.
  int inizio = 0;
  // Il tempo massimo che possiamo coprire con gli intervalli già valutati.
  int fine = 0;

  // Il numero di persone che devono essere assunte.
  int conteggio = 0;

  for (const Intervallo& intervallo : intervalli) {
    if (intervallo.inizio > inizio) {
      // Sono finiti gli intervalli che ci permettono di dare continuità alla copertura.
      // Vediamo i precedenti fino a dove ci permettono di coprire.
      
      // Dovremo iniziare a ricercare dal tempo appena successivo a quello di fine già trovato.
      inizio = fine + 1;

      // Abbiamo assunto un'altra persona
      ++conteggio;

      // Possiamo lasciare `fine` invariato. Tanto è destinato a crescere.
    }

    // `fine` deve essere un massimo.
    // Non è detto che la soluzione ottima debba avere per forza il massimo. Tuttavia:
    // - Se non contiene il massimo possiamo provare a sostituire il primo intervallo con il massimo ed ottenere una soluzione ottima valida.
    // - La ricerca dei successivi intervalli è un sottoproblema del tutto analogo, ma con tempo di inizio differente. Possiamo ripetere lo stesso ragionamento.
    // Questa tecnica di approccio è detta GREEDY, stiamo facendo una scelta "ingorda": "meglio abbondare che deficere".
    // Ovviamente questa tecnica non è sempre applicabile per ottenere soluzioni ottime.
    fine = max(fine, intervallo.fine);

    // Può tranquillamente succedere che finiscano gli intervalli senza che si esca dalla zona di copertura (ossia non si entra nell'if precedente).
    // Ciò può comportare che l'ultimo intervallo di copertura non venga conteggiato.
    // Gestiamo l'evento come caso particolare.
    // Ciò ci permette inoltre di terminare in anticipo.
    //
    // ES caso limite:
    // - Abbiamo coperto fino al giorno 50.
    // - C'è un intervallo che inizia al giorno 10 e termina al giorno 1000, ossia la fine delle vacanze.
    // - Senza questo if dovremmo continuare ad iterare tutti gli intervalli che cominciano fra il giorno 10 e il giorno 50 prima di accettare questo stesso intervallo.
    if (fine >= K - 1) {
      ++conteggio;
      break;
    }
  }

  out << conteggio;

  in.close(); out.close();
}
