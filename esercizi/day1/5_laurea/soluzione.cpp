#include <bits/stdc++.h>
using namespace std;

// Struttura per organizzare i veicoli.
struct Veicolo {
  // numero di posti nel veicolo
  int posti;

  // numero di veicoli disponibili
  int numero;

  // costo del veicolo
  int costo;
};

// Creiamo un array di 4 veicoli.
vector<Veicolo> veicoli(4);

// Il risultato che vogliamo migliorare pian piano.
// Inizializziamo a `numeric_limits<int>::max()`, ossia il valore massimo rappresentabile dal tipo `int`.
// In realtà, dalle ipotesi del problema sappiamo già che non possono essere superati i 100·100 euro (si può raffinare ancora di più la stima).
int costo_minimo = numeric_limits<int>::max();

// Funzione RICORSIVA per il calcolo delle combinazioni.
// `indice_veicolo` è l'indice del primo veicolo che possiamo prendere.
// `persone_rimanenti` è il numero di persone che sono ancora in attesa.
// `costo_attuale` sono i soldi già spesi.
void combinazioni(int indice_veicolo, int persone_rimanenti, int costo_attuale) {

  // Se non ci sono più persone in attesa allora abbiamo concluso.
  if (persone_rimanenti <= 0) {
    // Aggiorniamo il costo ottenuto, se necessario.
    costo_minimo = min(costo_minimo, costo_attuale);
    // Torniamo indietro per provare un'altra possibilità.
    return;
  }

  // Se sono finiti i veicoli (ma non le persone) allora non siamo giunti ad una soluzione. Torniamo indietro.
  if (indice_veicolo >= veicoli.size()) {
    return;
  }

  // Salviamo il veicolo per riferimento! In modo da accedervi direttamente.
  const Veicolo& veicolo = veicoli.at(indice_veicolo);

  // Possiamo prendere i veicoli di una certa tipologia tutti in uno stesso momento.
  // Prenderli prima o dopo non fa differenza dato che il costo è sempre quello e anche se sono mezzi vuoti non cambia nulla.
  
  // Cerchiamo di prendere più veicoli migliori possibili, per cercare una soluzione "buona".
  // Possiamo anche prendere 0 veicoli di questo tipo.
  for (int numero = veicolo.numero; numero >= 0; --numero) {
    // Proviamo a soddisfare le altre persone con i prossimi veicoli.
    // Non ha senso riprovare ad utilizzare questo veicolo (o precedenti) dato che è equivalente a prenderne di più in questo momento. Ma abbiamo già provato a prenderne di più.
    // Abbiamo soddisfatto al massimo `veicolo.posti * numero` persone. Anche se andiamo in negativo non è un problema.
    // Abbiamo speso ulteriori `veicolo.costo * numero` euro.
    combinazioni(indice_veicolo + 1, persone_rimanenti - veicolo.posti * numero, costo_attuale + veicolo.costo * numero);
  }

}


int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // Numero di persone.
  int N; in >> N;

  // Inizializziamo il numero di posti dei vari veicoli.
  veicoli[0].posti = 2;
  veicoli[1].posti = 4;
  veicoli[2].posti = 5;
  veicoli[3].posti = 7;

  // Il veicolo deve essere letto per riferimento! Lo dobbiamo modificare (e in ogni caso è meglio non fare copie inutili).
  for (Veicolo& veicolo : veicoli) {
    in >> veicolo.numero >> veicolo.costo;
  }

  // Proviamo le varie combinazioni.
  // Partiamo dal veicolo 0. Dobbiamo trasportare `N` persone. Abbiamo già speso 0 euro.
  combinazioni(0, N, 0);

  out << costo_minimo;

  in.close(); out.close();
}
