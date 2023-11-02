#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di elementi: parametro del problema.
  int N;
  in >> N;

  // Una somma pari può essere ottenuta come pari+pari o dispari+dispari.
  // La somma massima è ottenuta dalla somma fra i due pari più grandi o i due dispari più grandi.
  
  // `massimi.at(0)` è il massimo pari (non la somma, proprio l'elemento) trovato fino a questo momento.
  // `massimi.at(1)` è il massimo dispari trovato fino a questo momento.
  // Questo è un array: ha dimensione fissa ed ha un'interfaccia simile a `vector`.
  array<int, 2> massimi{-1, -1};

  // Somma massima pari trovata.
  // Inizializzato come per l'esercizio precedente.
  int somma_massima = -1;

  for (int i = 0; i < N; ++i) {
    int num; in >> num;

    // È una reference! Cosi poi la posso modificare.
    int& massimo = massimi.at(num % 2);

    // Come per la ricerca del massimo "standard", possiamo andare ad aggiornare `somma_massima` pian piano che valutiamo gli elementi.
    // Vogliamo che `somma_massima` abbia sempre il valore della somma massima pari del sottovettore analizzato fino a questo momento.

    // Esiste già un altro valore pari/dispari. 
    if (massimo >= 0) {
      // Sommiamo `num` con il massimo dei valori pari/dispari precedenti.
      // Qualsiasi altra somma di `num` con gli valori pari/dispari precedenti sarà sicuramente minore (o uguale) di questa somma.
      // Aggiorniamo `somma_massima` se possibile.
      somma_massima = max(somma_massima, massimo + num);
    }

    // Aggiorniamo `massimo` se possibile.
    massimo = max(massimo, num);
  }

  out << somma_massima;

  in.close(); out.close();
}
