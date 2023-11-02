#include <bits/stdc++.h>
using namespace std;

// Questo è un DEFINE.
// Tutte le righe che iniziano con `#` sono dette "istruzioni per il preprocessore".
//
// Il preprocessore è uno strumento che viene eseguito prima della compilazione e che effettua sostituzioni.
//
// Per esempio: con `include` prende il file 'bits/stdc++.h' e lo sostituisce ad `include`.
// Con `define` prende tutti i `MAX` nel testo e li sostituisce con il valore `7`.
// Il preprocessore ha anche altre funzionalità.

// Le tessere possono assumere valori fra 0 e 6 compresi: 7 valori.
#define MAX 7

// Creiamo una MATRICE (ossia una tabella 7x7). Può essere vista come array delle righe.
// Nella cella (a, b) andiamo a contare quante tessere [a b] e [b a] abbiamo (ancora) disponibili.
// Inizialmente non abbiamo alcuna tessera: inizializziamo a 0.
vector<vector<int>> tessere(MAX, vector<int>(MAX, 0));

// Con "backtracking" si intende "provare tutte le combinazioni per poi tornare indietro e provarne altre".
// È una tecnica che viene implementata con funzioni RICORSIVE.
// È proprio quello che fa il nostro algoritmo.
// `estremo` è il valore del primo estremo, per poterci collegare alla catena già creata.
int backtracking(int estremo) {

  // Salviamo la riga delle tessere `estremo`-? per facilità di accesso.
  auto& riga = tessere.at(estremo);

  // Possiamo applicare tutte le tessere [estremo estremo] in questo momento.
  // Non utilizzarle proprio riduce sicuramente la lunghezza della sequenza.
  // Data una soluzione [? estremo][estremo ?] possiamo sicuramente costruirne una [? estremo][estremo estremo][estremo ?]
  // Utilizzarle più avanti non permette di ottenere sequenze più lunghe.
  // Questa variabile memorizza quante tessere di questo tipo abbiamo.
  const int num_tessere_ii = riga.at(estremo);
  // Applichiamo le tessere [estremo estremo], non potremo impiegarle più avanti.
  riga.at(estremo) = 0;

  // Dobbiamo ricercare un massimo. Questa è la lunghezza massima parziale della sequenza costruibile con le tessere rimanenti e iniziando con `estremo`.
  // Inizializziamo a 0 perchè è l'evenienza in cui non sia possibile collegare nessun'altra tessera.
  int massima_lunghezza = num_tessere_ii;

  // Proviamo un qualsiasi altro estremo.
  for (int altro_estremo = 0; altro_estremo < MAX; ++altro_estremo) {
    // Se non è rimasta nessuna tessera `estremo`-`altro_estremo` allora non possiamo proseguire.
    if (riga.at(altro_estremo) <= 0) continue;

    // Stiamo usando una tessera `estremo`-`altro_estremo`. Non sarà più possibile impiegarla in futuro.
    tessere.at(altro_estremo).at(estremo) = --riga.at(altro_estremo);

    // Aggiorniamo la lunghezza massima se possibile.
    // Proviamo tutte le combinazioni sapendo che si devono collegare ad `altro_estremo`.
    // Il +1 serve a conteggiare anche la tessera `estremo`-`altro_estremo` che abbiamo aggiunto qui. Aggiungiamo anche tutte le tessere `estremo`-`estremo`.
    massima_lunghezza = max(massima_lunghezza, backtracking(altro_estremo) + 1 + num_tessere_ii);

    // Torniamo indietro per provare altre possibilità.
    // Rimettiamo la tessera `estremo`-`altro_estremo` nel sacchetto delle tessere.
    tessere.at(altro_estremo).at(estremo) = ++riga.at(altro_estremo);
  }

  // Ripristiniamo il numero di tessere, è un algoritmo di backtracking.
  riga.at(estremo) = num_tessere_ii;

  // Ritorniamo la lunghezza massima. Eventualmente 0 se non siamo riusciti ad aggiungere nessun'altra tessera.
  return massima_lunghezza;
}

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  // estremo di tessere
  int N; in >> N;

  for (int i = 0; i < N; ++i) {
    int a, b; in >> a >> b;

    // Incrementiamo il conteggio sia delle tessere a-b che delle tessere b-a. Tanto possiamo girare questa tessera a piacimento.
    //
    // L'operatore ++(...) permette di incrementare `tessere.at(b).at(a)` e restituisce il valore post incremento.
    // Valore che poi viene assegnato a `tessere.at(a).at(b)`.
    tessere.at(a).at(b) = ++tessere.at(b).at(a);
  }

  // Ricerca della lunghezza massima.
  int massima_lunghezza = 0;

  // Possiamo partire con una cella qualsiasi.
  // Sfruttiamo la funzione `bruteforce` e "facciamo finta" di vincolare uno degli estremi delle tessere. Tuttavia li proviamo tutti.
  for (int i = 0; i < MAX; ++i) {
    // Aggiorniamo la lunghezza massima se necessario.
    // Chiamiamo il `backtracking` in modo che inizi con l'estremo `i`.
    //
    // Qui non c'è il +1 perchè non abbiamo aggiunto nessuna tessera.
    massima_lunghezza = max(massima_lunghezza, backtracking(i));
  }

  out << massima_lunghezza;

  in.close();
  out.close();
}
