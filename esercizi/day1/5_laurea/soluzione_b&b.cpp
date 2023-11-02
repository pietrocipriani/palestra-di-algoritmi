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

// Introduciamo il concetto di "qualità-prezzo": è dato da `posti`/`costo`.
// Un veicolo è "migliore" se ha un rapporto qualità/prezzo migliore.
// Questa è la definizione di un OPERATORE: ci permette di scrivere
// ```
// Veicolo v1, v2;
// ...
// if (v1 < v2) {
//   ... 
// }
// ```
//
// ATTENZIONE: `std::sort`, di default, ordina con `std::less`. Ossia vuole proprio l'operatore `<`! Non è la stessa cosa usare il `>`.
bool operator<(const Veicolo& v1, const Veicolo& v2) {
  // `>` invece che `<`. `sort` ha un ordine crescente. Noi vogliamo però i veicoli migliori per primi.
  // Basta stabilire che v1 < v2 quando il suo rapporto qualità/prezzo è più elevato.
  return (double) v1.posti / v1.costo > (double) v2.posti / v2.costo;
} 

// Creiamo un array di 4 veicoli.
array<Veicolo, 4> veicoli;


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

  // OPZIONALE: Stiamo analizzando il veicolo migliore che ci è rimasto.
  // Ci calcoliamo il "costo per posto" per questo veicolo: `costo/posti`.
  //
  // Essendo il reciproco della qualità/prezzo ed essendo questo veicolo il migliore (rimaente), allora questo veicolo ha il "costo per posto" più basso.
  // ATTENZIONE: se non si effettua l'ordinamento nel main allora non si può effettuare nemmeno questa stima. Perchè non siamo più sicuri che abbia il "costo per posto" migliore.
  //
  // Possiamo stimare a ribasso il costo finale come `costo_attuale` + "posti rimanenti" · "costo per posto".
  // Con "posti rimanenti" · "costo per posto" si ottiene una stima a ribasso del costo per le persone rimanenti.
  // `proiezione_costo` diventa quindi una stima a ribasso del costo finale.
  // "posti rimanenti" è `persone_rimanenti`.
  // Anche la divisione arrotonda a ribasso.
  int proiezione_costo = costo_attuale + persone_rimanenti * veicolo.costo / veicolo.posti;
  
  // Se la proiezione del costo è superiore alla soluzione migliore trovata fino ad ora allora, dato che la situazione può solo che peggiorare, possimo escludere direttamente questa soluzione.
  //
  // PS: anche NON effettuando la proiezione del costo OPZIONALE qui sopra si poteva in ogni caso controllare che il `costo_attuale` non fosse superiore al `costo_minimo`.
  // Semplicemente equivale a fare una stima ancora più a ribasso con il costo aggiuntivo per i posti rimanenti pari a €0.
  if (proiezione_costo >= costo_minimo) {
    return;
  }

  // Possiamo prendere i veicoli di una certa tipologia tutti in uno stesso momento.
  // Prenderli prima o dopo non fa differenza dato che il costo è sempre quello e anche se sono mezzi vuoti non cambia nulla.
  
  // OPZIONALE: Troviamo qual è il numero massimo di veicoli di questo tipo che ci possono servire.
  // Possiamo anche prenderli tutti, tuttavia prendere veicoli che rimarranno vuoti ci costerà sicuramente di più.
  // Ovviamente il numero massimo di veicoli non può superare il numero di veicoli di questo tipo.
  //
  // `+ veicolo.posti - 1` serve ad arrotondare per eccesso.
  int numero_massimo = min(veicolo.numero, (persone_rimanenti + veicolo.posti - 1) / veicolo.posti);

  // Cerchiamo di prendere più veicoli migliori possibili, per cercare una soluzione "buona".
  // Possiamo anche prendere 0 veicoli di questo tipo.
  for (int numero = numero_massimo; numero >= 0; --numero) {
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

  // Inizializziamo il numero di posti.
  veicoli[0].posti = 2;
  veicoli[1].posti = 4;
  veicoli[2].posti = 5;
  veicoli[3].posti = 7;

  // Il veicolo deve essere letto per riferimento! Lo dobbiamo modificare (e in ogni caso è meglio non fare copie inutili).
  for (Veicolo& veicolo : veicoli) {
    in >> veicolo.numero >> veicolo.costo;
  }

  // OPZIONALE: È probabile che un veicolo con buon rapporto qualità prezzo venga preso in una soluzione ottima.
  // Possiamo dunque provare a prendere prima i veicoli migliori e pian piano che finiscono andiamo a prendere gli altri.
  //
  // ATTENZIONE: Facciamo finta che i veicoli disponibili siano:
  // - 2 x 5 posti - € 10
  // - 1 x 7 posti - € 13
  // - 1 x 4 posti - € 9
  // Dobbiamo trasportare 10 persone.
  // Il veicolo con la migliore qualità prezzo è quello da 7 posti.
  // Possiamo trasportare le persone come 7+4 con un costo di 22 euro.
  // Con un 5+5 si potevano spendere 20 euro.
  // Si può verificare che il problema non è dovuto al fatto di aver sforato il numero di posti (se esempio fosse esistito un veicolo da 3 posti con lo stesso costo del 4 posti).
  //
  // Il problema è che l'algoritmo semplicemente NON è CORRETTO.
  //
  // Possiamo comunque supporre che ci permetta di arrivare ad una "buona" soluzione.
  // Possiamo quindi comunque partire dai veicoli migliori, ma comunque provare un po' tutte le combinazioni.
  // L'idea è che trovare "buone" soluzioni sin da subito ci permette di eliminare alcune possibilità più avanti.
  sort(veicoli.begin(), veicoli.end());

  // Proviamo le varie combinazioni.
  // Partiamo dal veicolo 0. Dobbiamo trasportare `N` persone. Abbiamo già speso 0 euro.
  combinazioni(0, N, 0);

  out << costo_minimo;

  in.close(); out.close();
}
