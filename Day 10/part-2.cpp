#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

int get_character_score(char c) {
  switch (c) {
    case PAREN_CLOSE:
      return 1;
    case BRACK_CLOSE:
      return 2;
    case BRACE_CLOSE:
      return 3;
    case ANGLE_CLOSE:
      return 4;
    default:
      return 0;
  }
}

unsigned long long int score(std::vector<char>& completion_string) {
  unsigned long long int score = 0;
  for (size_t i = 0; i < completion_string.size(); i++) {
    score *= 5;
    score += get_character_score(completion_string[i]);
  }
  return score;
}

std::vector<char> get_completion_string(stack<char>& chars) {
  std::vector<char> completion_string;
  while (!chars.empty()) {
    switch (chars.pop()) {
      case PAREN_OPEN:
        completion_string.push_back(PAREN_CLOSE);
        break;
      case BRACK_OPEN:
        completion_string.push_back(BRACK_CLOSE);
        break;
      case BRACE_OPEN:
        completion_string.push_back(BRACE_CLOSE);
        break;
      case ANGLE_OPEN:
        completion_string.push_back(ANGLE_CLOSE);
        break;
      default:
        break;
    }
  }
  return completion_string;
}

unsigned long long int parse_line(std::string& line) {
  stack<char> stack;
  for (char c : line) {
    if (contains(c, OPENS)) {
      stack.push(c);
    } else if (contains(c, CLOSES)) {
      if (stack.empty()) {
        return -1;
      }
      char open = stack.pop();
      if (!matches(open, c)) {
        return -1;
      }
    }
  }
  return score(get_completion_string(stack));
}

unsigned long long int parse_file(std::ifstream& file) {
  std::string line;
  std::vector<unsigned long long int> scores;
  while (!file.eof()) {
    std::getline(file, line);
    unsigned long long int score = parse_line(line);
    if (score != -1) {
      scores.push_back(parse_line(line));
    }
  }
  std::sort(scores.begin(), scores.end());
  return scores[scores.size() / 2];
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  return 0;
}
