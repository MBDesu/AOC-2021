#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stack.hpp"

const auto BRACK_OPEN = '[';
const auto BRACE_OPEN = '{';
const auto PAREN_OPEN = '(';
const auto ANGLE_OPEN = '<';
const auto BRACK_CLOSE = ']';
const auto BRACE_CLOSE = '}';
const auto PAREN_CLOSE = ')';
const auto ANGLE_CLOSE = '>';

const std::vector<char> OPENS = { BRACK_OPEN, BRACE_OPEN, PAREN_OPEN, ANGLE_OPEN };
const std::vector<char> CLOSES = { BRACK_CLOSE, BRACE_CLOSE, PAREN_CLOSE, ANGLE_CLOSE };

bool contains(char& needle, std::vector<char> haystack) {
  for (auto character : haystack) {
    if (character == needle) {
      return true;
    }
  }
  return false;
}

bool matches(char open, char close) {
  return open == BRACK_OPEN && close == BRACK_CLOSE
      || open == BRACE_OPEN && close == BRACE_CLOSE
      || open == PAREN_OPEN && close == PAREN_CLOSE
      || open == ANGLE_OPEN && close == ANGLE_CLOSE;
}

int score(char c) {
  switch (c) {
    case PAREN_CLOSE:
      return 3;
    case BRACK_CLOSE:
      return 57;
    case BRACE_CLOSE:
      return 1197;
    case ANGLE_CLOSE:
      return 25137;
    default:
      return 0;
  }
}

int parse_line(std::string& line) {
  stack<char> stack;
  for (char c : line) {
    if (contains(c, OPENS)) {
      stack.push(c);
    } else if (contains(c, CLOSES)) {
      if (stack.empty()) {
        return 0;
      }
      char open = stack.pop();
      if (!matches(open, c)) {
        // std::cout << "Mismatched " << open << " and " << c << std::endl;
        return score(c);
      }
    }
  }
  return 0;
}

int parse_file(std::ifstream& file) {
  std::string line;
  int score = 0;
  while (!file.eof()) {
    std::getline(file, line);
    // std::cout << line << std::endl;
    score += parse_line(line);
  }
  return score;
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  return 0;
}
