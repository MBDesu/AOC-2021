#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int sum_next_lines(std::ifstream *file, int num_lines) {
  int sum = 0;
  for (int i = 0; i < num_lines && !file->eof(); i++) {
    char line[256];
    file->getline(line, sizeof(line));
    if (std::strlen(line) > 0) {
      sum += std::stoi(line);
    }
  }
  return sum;
}

// hack
void reset_file_position(std::ifstream *file, std::streampos old_pos, int num_lines_fwd) {
  file->seekg(old_pos);
  char dummy[256];
  for (int i = 0; i < num_lines_fwd && !file->eof(); i++) {
    file->getline(dummy, sizeof(dummy));
  }
}

int parse_file(std::ifstream *file) {
  int result = 0;
  int prev_sum = 0;
  while (!file->eof()) {
    std::streampos old_pos = file->tellg();
    int sum = sum_next_lines(file, 3);
    if (prev_sum > 0 && sum > prev_sum) {
      result++;
    }
    if (!file->eof()) {
      reset_file_position(file, old_pos, 1);
    }
    prev_sum = sum;
  }
  return result;
}

int main() {
  std::ifstream file;
  file.open("input.txt", std::ifstream::in);
  std::cout << parse_file(&file) << std::endl;
  file.close();
  return 0;
}
