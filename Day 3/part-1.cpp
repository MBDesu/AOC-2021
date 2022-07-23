#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <bits/stdc++.h>

int calc_epsilon(int gamma) {
  // the below line does work, but uh...bitset exists, I learned
  // return ~gamma ^ 0b1111111111111111111111111111111111111111111111111111000000000000;
  std::bitset<12> gamma_bits(gamma);
  std::bitset<12> epsilon_bits = gamma_bits.flip();
  return (int) epsilon_bits.to_ulong();
}

int calc_gamma(int *counts, int num_lines) {
  int gamma = 0;
  for (size_t i = 0; i < 12; i++) {
    int most_common = counts[i] > (num_lines / 2) ? 1 : 0;
    if (most_common) {
      gamma += pow(2, 11 - i);
    }
  }
  return gamma;
}

void parse_line(std::ifstream *file, int *counts) {
  char line[256];
  file->getline(line, sizeof(line));
  for (size_t i = 0; i < 12; i++) {
    counts[i] += line[i] - '0';
  }
}

int parse_file(std::ifstream *file) {
  int result = 0;
  int num_lines = 0;
  int counts[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  while (!file->eof()) {
    ++num_lines;
    parse_line(file, counts);
  }
  int gamma = calc_gamma(counts, num_lines);
  return gamma * calc_epsilon(gamma);
}

int main() {
  std::ifstream file;
  file.open("input.txt", std::ifstream::in);
  std::cout << parse_file(&file) << std::endl;
  return 0;
}
