#include <iostream>
#include <fstream>
#include <vector>
#include <string>
/**
 * This one isn't complete
 */
using namespace std;

template <typename T>

void print_vector(vector<T>& v) {
  for (size_t i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}

vector<string> split(const string& s, const string& delim) {
  vector<string> tokens;
  size_t prev = 0, pos;
  do {
    pos = s.find(delim, prev);
    if (pos == string::npos) {
      pos = s.length();
    }
    string token = s.substr(prev, pos - prev);
    tokens.push_back(token);
    prev = pos + delim.length();
  } while (pos < s.length() && prev < s.length());
  return tokens;
}

void parse_output_patterns(vector<string>& output_patterns, vector<int>& results) {
  for (size_t i = 0; i < output_patterns.size(); i++) {
    switch (output_patterns.at(i).length()) {
      case 2:
        results.push_back(1);
        break;
      case 3:
        results.push_back(7);
        break;
      case 4:
        results.push_back(4);
        break;
      case 7:
        results.push_back(8);
        break;
      default:
        break;
    }
  }
}

void parse_line(string line, vector<string>& signal_patterns, vector<string>& output_patterns) {
  // probably not the best way
  vector<string> signals = split(split(line, " |")[0], " ");
  vector<string> outputs = split(split(line, "| ")[1], " ");
  signal_patterns.insert(signal_patterns.end(), signals.begin(), signals.end());
  output_patterns.insert(output_patterns.end(), outputs.begin(), outputs.end());
}

int parse_file(ifstream& file) {
  vector<string> signal_patterns;
  vector<string> output_patterns;
  vector<int> results;
  while (!file.eof()) {
    string line;
    getline(file, line);
    parse_line(line, signal_patterns, output_patterns);
  }
  parse_output_patterns(output_patterns, results);
  // print_vector(output_patterns);
  // print_vector(results);
  return results.size();
}

int main() {
  ifstream file("sample.txt", ios::in);
  cout << parse_file(file) << endl;
  file.close();
  return 0;
}
