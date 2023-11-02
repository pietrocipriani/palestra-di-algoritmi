

input = open("input.txt", "r")
output = open("output.txt", "w")

# Numero di elementi: parametro del problema
N = int(input.readline())

# Leggo la riga degli S. Separo i "token" e li converto in numeri interi.
# Potrebbe dare dei problemi nel caso vi siano più di uno spazio fra i numeri o nel caso rimangano dei "whitespaces" a fine riga.
# Lo `strip` serve ad evitare che vi siano caratteri "strani" a inizio e fine riga (new line o spazi che potrebbero dare più split del dovuto).
# I caratteri in mezzo ai numeri possono comunque creare problemi.
Ss = [ int(S) for S in input.readline().strip().split(' ') ]

# controllo che effettivamente il numero di S sia pari a N
assert N == len(Ss), "mmm... qualcosa non va"

for S in Ss:
    # `all` può essere implementato manualmente come:
    # def all(vettore):
    #   for elemento in vettore:
    #       if elemento == False: return False
    #   return True

    # Vogliamo controllare se `S` è maggiore o uguale di tutti gli altri valori in `Ss`
    maggiore = all(S >= altro_valore for altro_valore in Ss)
    # Curiosità
    # In C++ si poteva fare come:
    # 
    # auto predicato = [&](int altro_valore) {
    #   return S >= altro_valore;
    # };
    # bool maggiore = all_of(Ss.begin(), Ss.end(), predicato);
    #
    # Tuttavia non mi sembrava il caso di introdurre la sintassi delle _lambda_.

    # Se `S` è maggiore di tutti gli altri allora è il massimo
    if maggiore:
        output.write(str(S))
        # Abbiamo terminato la nostra ricerca
        break


input.close()
output.close()

