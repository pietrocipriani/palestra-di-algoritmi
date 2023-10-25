#include <stdio.h>
#include <stdlib.h>

// stampa l'"oggetto" `obj` su `stderr`. Stampa solamente quando `DEBUG` è stato definito.
#ifdef DEBUG
  #define debug(obj) (clog << (obj))
#else
  #define debug(obj)
#endif

// Definizione di variabili globali per poter agevolmente chiamare funzioni senza doversi preoccupare dei parametri.
// TODO: variabili globali


// Funzione da implementare per la lettura di "input.txt" e la risoluzione del problema.
void read_and_solve() {

  // TODO: lettura / elaborazione

  fclose(stdin);

  // TODO: implementazione algoritmo

}


int main(int argc, const char **argv) {

  // Apro "input.txt" e lo associo a `stdin` in lettura (lo stream originale viene chiuso).
  // In questo modo `cin` e eventualmente tutto ciò che fa riferimento a `stdin` (scanf...) leggerà da questo file. 
  if (freopen("input.txt", "r", stdin) == NULL) {
    // Errore nell'apertura di "input.txt". Abort.
    perror("Impossibile aprire \"input.txt\"");
    return EXIT_FAILURE;
  }

  // Se definiamo `TERMINAL` allora stampiamo sul terminale, altrimenti in "output.txt".
  // ES: g++ -DTERMINAL main.cpp
  #ifndef TERMINAL
    // Apro "output.txt" e lo associo a `stdout` in scrittura.
    if (freopen("output.txt", "w", stdout) == NULL) {
      fclose(stdin);
      perror("Impossibile aprire \"output.txt\"");
      return EXIT_FAILURE;
    }
  #endif // TERMINAL
  
  // lettura dell'input e risoluzione del problema.
  read_and_solve();

  fclose(stdin); fclose(stdout);

  return EXIT_SUCCESS;

}
