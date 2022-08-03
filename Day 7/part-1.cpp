#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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

int least_fuel(vector<int>& crabs) {
  int least_fuel = INT_MAX;
  for (size_t i = 0; i < crabs.size(); i++) {
    int fuel = 0;
    for (size_t j = 0; j < crabs.size(); j++) {
      fuel += abs(crabs[i] - crabs[j]);
    }
    least_fuel = min(fuel, least_fuel);
  }
  return least_fuel;
}

int parse_file(ifstream& file) {
  string line;
  vector<string> tokens;
  vector<int> crabs;
  getline(file, line);
  tokens = split(line, ",");
  for (size_t i = 0; i < tokens.size(); i++) {
    crabs.push_back(stoi(tokens[i]));
  }
  return least_fuel(crabs);
}

int main() {
  ifstream file("input.txt", ios::in);
  cout << parse_file(file) << endl;
  file.close();
  return 0;
}
