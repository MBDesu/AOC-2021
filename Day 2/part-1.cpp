#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

void parse_command(const char *command, int magnitude, int *result) {
  switch (command[0]) {
    case 'f':
      result[0] += magnitude;
    break;
    case 'd':
      result[1] += magnitude;
    break;
    case 'u':
      result[1] -= magnitude;
    break;
    default:
    break;
  }
}

void parse_line(std::ifstream *file, int *result) {
  char line[256];
  std::vector<char *> tokens_v;
  file->getline(line, sizeof(line));
  if (std::string(line).length() > 0) {
    char *tokens = std::strtok(line, " ");
    while (tokens) {
      tokens_v.push_back(tokens);
      tokens = std::strtok(NULL, " ");
    }
    parse_command(tokens_v.at(0), std::stoi(tokens_v.at(1)), result);
  }
}

int parse_file(std::ifstream *file) {
  int result = 0;
  int encoded_result[2] = { 0, 0 }; // x, y
  while (!file->eof()) {
    parse_line(file, encoded_result);
  }
  result = encoded_result[0] * encoded_result[1];
  return result;
}

int main() {
  std::ifstream file;
  file.open("input.txt", std::ifstream::in);
  std::cout << parse_file(&file) << std::endl;
  file.close();
  return 0;
}
