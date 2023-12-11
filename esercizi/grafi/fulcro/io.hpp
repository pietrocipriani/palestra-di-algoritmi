#pragma once
#include <cstdlib>
#include <cstdio>
#include <cstdint>

template<size_t size>
class FastIO {
private:
  char buffer[size];
  size_t index;

public:
  FastIO(const char * path);

  template<typename T>
  T read_num();
  template<typename T>
  T read_signed();
};

template<size_t size>
FastIO<size>::FastIO(const char * path) {
  FILE * in = fopen(path, "r");
  fread_unlocked(buffer, sizeof(*buffer), size, in);
  fclose(in);
} 

template<size_t size>
template<typename T>
T FastIO<size>::read_num() {
  T n = 0;
  char c;
  do {
    c = buffer[index++];
  } while (c < '0' || c > '9');
  while (c >= '0' && c <= '9') {
    n = n * 10 + (c - '0');
    c = buffer[index++];
  }
  return n;
}

template<size_t size>
template<typename T>
T FastIO<size>::read_signed() {
  T n = 0;
  char c;
  do {
    c = buffer[index++];
  } while ((c < '0' || c > '9') && c != '-');
  bool neg = c == '-';
  if (neg) c = buffer[index++];
  while (c >= '0' && c <= 9) {
    n = n * 10 + (c - '0');
    c = buffer[index++];
  }
  if (neg) return -n;
  return n;
}
