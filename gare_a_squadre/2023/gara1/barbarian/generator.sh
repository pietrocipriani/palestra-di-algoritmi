#!/bin/bash

g++ -Wall -Wextra -Wpedantic validator.cpp

sub1() {
  echo 5 > input/input0.txt
  echo 1 4 6 7 10 >> input/input0.txt
  echo "4 0 4 4 0" > output/output0.txt
}

sub2() {
  for i in $(seq "$1" "$2"); do
    echo "$4" > input.txt
    shuf -i "0-$3" -n "$4" | sort -n | tr '\n' ' ' >> input.txt
    ./a.out
    mv input.txt input/input$i.txt
    mv output.txt output/output$i.txt
  done
}

sub1
sub2 1 4 1000000000 100
sub2 5 10 1000000000000 1000

zip -r io.zip input/ output/
