import java.io.FileInputStream;
import java.io.PrintStream;
import java.io.IOException;
import java.util.*;

class Template {
  // "flag" per stabilire se stampare su terminale o su "output.txt".
  private static final boolean TERMINAL = false;
  // "flag" per stabilire se stampare i messaggi di debug.
  private static final boolean DEBUG = false;
  
  // Definizione di variabili statiche per poter agevolmente chiamare funzioni senza doversi preoccupare dei parametri.
  // TODO: variabili statiche "globali"
  
  
  // Funzione da implementare per la lettura di "input.txt" e la risoluzione del problema.
  private static void read_and_solve() throws IOException {
    // `Scanner` per leggere più facilmente.
    try (final Scanner in = new Scanner(System.in)) {

      // TODO: lettura / elaborazione

    }
    
    // TODO: implementazione algoritmo
  }
  
  
  public static void main(final String[] args) throws IOException {
  
    // Apro "input.txt" e lo associo a `System.in` in lettura.
    System.setIn(new FileInputStream("input.txt"));
  
    // Se abbiamo settato la flag `TERMINAL` allora stampiamo sul terminale, altrimenti in "output.txt".
    if(!TERMINAL) {
      // Apro "output.txt" e lo associo a `stdout` in scrittura.
      System.setOut(new PrintStream("output.txt"));
    }
    
    // lettura dell'input e risoluzione del problema.
    read_and_solve();

    System.out.close();
  
  }

  // Funzione per stampare messaggi di debug quando richiesto.
  private static void debug(final Object... objs) {
    if (!DEBUG) return;
    for (final Object obj : objs) System.err.print(obj);
    System.out.println("");
  }

}
