#!/bin/bash

if [ $# -ne 1 ]
then
  echo "Usage: $0 <source file>" > /dev/stderr
  exit 1
fi

# salviamo la path del source file
SOURCE="$1"

if ! [ -e "$SOURCE" ]
then
  echo "Il file '$SOURCE' non esiste." > /dev/stderr
  exit 1
fi

# salviamo la cartella che contiene gli inputs/outputs.
DIR="$(dirname "$SOURCE")"
# file zip contenente i test
ZIP="$DIR/io.zip"

if ! [ -e "$ZIP" ]
then
  echo "La cartella non contiene test locali." > /dev/stderr
  exit 1
fi

trap 'rm -rf "$TMPDIR"' EXIT

# creiamo una cartella temporanea dove scompattare gli i/o e lanciare l'esecuzione.
TMPDIR="$(mktemp -d)"

if ! unzip "$ZIP" -d "$TMPDIR" 2> "$TMPDIR/log.txt" > /dev/null
then
  cat log.txt > /dev/stderr
  echo "Errore durante la scompattazione del file zip." > /dev/stderr
  exit 1
fi

# cartelle degli inputs e outputs
INPUTS="$TMPDIR/input"
OUTPUTS="$TMPDIR/output"

if ! [ -d "$INPUTS" -a -d "$OUTPUTS" ]
then
  echo "Il file zip non contiene /input e /output." > /dev/stderr
  exit 1
fi

# file eseguibile derivato dalla compilazione di $SOURCE
SOLVER="$TMPDIR/solver"

if ! g++ -Wall -Wextra -Wpedantic -fsanitize=address -g "$SOURCE" -o "$SOLVER"
then
  echo "Errore durante la compilazione del file fornito." > /dev/stderr
  exit 1
fi

echo "Compilazione completata."

cd "$TMPDIR"

for file in $(ls -v $INPUTS/input*.txt); do
  FILENAME="$(basename $file)"
  if ! grep -Pq '^input[0-9]+\.txt$' <<< "$FILENAME"
  then
    echo "Ignorato il file $file. Nome non canonico."
    continue
  fi

  # Seleziono il numero dell'input
  NUMBER="$(grep -Po '[0-9]+' <<< "$FILENAME")"
  OUTPUT="$OUTPUTS/output$NUMBER.txt"
  if ! [ -f "$OUTPUT" ]
  then
    echo "Ignorato il file $file. Impossibile trovare il corrispondente output."
    continue
  fi

  rm -f "$TMPDIR/output.txt"
  cp "$file" "$TMPDIR/input.txt"
  $SOLVER

  if diff -qEZbB "$OUTPUT" "$TMPDIR/output.txt"
  then
    echo -e "Test $NUMBER \e[1;32mOK\e[m"
  else
    echo -e "Test $NUMBER \e[1;31mFAIL\e[m"
  fi
done
