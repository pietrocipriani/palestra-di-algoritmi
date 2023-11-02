#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int G, P; in >> G >> P;

  // Utilizziamo la matematica per trovare una formula per il numero di gemme che si prende Totò.
  // Siano `N` il numero di iterazioni di distribuzioni effettuate.
  // Il numero di gemme distribuite è dato da:
  // P + (P+1) + (P+2) + (P+3) + ... + (P+N-1)
  //
  // Si può dimostrare che tale somma può essere scritta come `(P+(P+N-1))·N / 2 = N²/2 + (2·P-1)·N/2`
  //
  // Noi vogliamo distribuire G gemme, ossia la somma deve essere = `G`.
  // 
  // Risolvendo per `N` si ottiene il numero di iterazioni.
  // ATTENZIONE: non è detto che sia possibile distribuire tutte le gemme con un numero di iterazioni esatte. Arrotondiamo per difetto in modo da avere il numero di iterazioni che sono andate a buon fine e gestiamo "manualmente" le gemme rimanenti.
  // N = floor( 0.5 - P + sqrt(0.25 + P² - P + 2·G) )
  // ATTENZIONE: con `N` "quasi esatto" potrebbero esserci degli errori di approssimazione che rendono il calcolo di `N`, una volta arrotondato, sbagliato.
  // ATTENZIONE anche agli overflow.
  //
  // Per evitare queste problematiche è possibile applicare il principio della "ricerca dicotomica/binaria" per trovare il valore di `N` in log(N).
  int N = 0.5 - P + sqrt(0.25 + P * P - P + 2 * G);

  // In queste `N` iterazioni, Totò prende 1 + ... + N gemme. Ossia `N·(N + 1) / 2` gemme.
  int gemme_toto = N * (N + 1) / 2;

  // Le gemme rimanenti dopo le `N` iterazioni
  G -= (2 * P + N - 1) * N / 2;
  
  // Aggiungiamo le gemme dell'ultima iterazione incompleta.
  gemme_toto += min(G, N + 1);
  
  out << gemme_toto;

  in.close(); out.close();
}
