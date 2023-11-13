#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main() {
  ifstream in("input.txt");
  ofstream out("output.txt");

  int N, M; in >> N >> M;

  // Lanciando il programma precedente e facendoci stampare la sequenza è possibile osservare come spesso e volentieri la sequenza si stabilizzi su uno stesso valore.
  //
  // Possiamo dimostrare che quando vi sono due valori uguali allora la sequenza rimarrà costante da quel momento in poi:
  // f(i) = ((i - 1) * f(i-1) - sum) mod M.
  // Sappiamo inoltre che f(i) = f(i - 1).
  // f(i + 1) = (i * f(i) - sum') mod M = (i * f(i-1) - sum - f(i-1)) mod M = ((i - 1) * f(i-1) - sum) mod M = f(i).
  // Il penultimo passaggio è giustificato dal fatto che f(i) = f(i-1) e che sum' = sum + f(i-1).
  // Abbiamo ottenuto che f(i+1) = f(i) = f(i-1), iterando il ragionamento possiamo dimostrare che tutti gli f(i') successivi saranno uguali a f(i).
  //
  // Quindi una volta che otteniamo `next` = `prev` possiamo terminare dato che il nostro f(N) sarà proprio uguale a `prev`.
  //
  // Mancherebbe da dimostrare che effettivamente prima o poi si arriva ad uno stato di stabilità e di fare una stima del valore / velocità con cui si giunge a questo valore.

  int sum = M - 1;
  
  int prev = 0;

  for (int i = 2; i <= N; ++i) {
    // Possiamo un po' alleggerire le operazioni di modulo.
    // `sum` e `prev` sono già mod M.
    // Dato che `i` <= 1_000_000 e `prev` <= 40_000 il loro prodotto può essere rappresentato da un intero a 64 bit senza troppi problemi.
    //
    // ATTENZIONE: 'https://en.cppreference.com/w/cpp/language/types#Data_models' per reference:
    // - Windows è un LLP64, ossia per avere un intero a 64 bit bisogna usare un `long long int`.
    // - Linux è un LP64, ossia per avere un intero a 64 bit bisogna usare un `long int`.
    // O andate sul sicuro con il `long long int`, oppure impiegate gli 'stdint'.
    //
    // (i-1) * prev è sicuramente >= 0, - sum otteniamo un valore >= -M, +M otteniamo un valore >= 0. Con il %M lo riportiamo nel range tra 0 e M.
    int next = ((int64_t) (i - 1) * prev - sum + M) % M;

    // Per le osservazioni fatte prima:
    if (prev == next) break;

    sum += prev;
    sum %= M;
    prev = next;
  }

  out << prev;

  in.close(); out.close();
}
