#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int parse_file(std::ifstream *file) {
  int result = 0;
  std::string prev_line;
  while (!file->eof()) {
    char line[256];
    file->getline(line, sizeof(line));
    if (prev_line.length() > 0 && std::strlen(line) > 0) {
      if (std::stoi(line) > std::stoi(prev_line)) {
        result++;
      }
    }
    prev_line.assign(line);
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
