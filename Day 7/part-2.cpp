#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

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

int sum_vector(vector<int> v) {
  int sum = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sum += v[i];
  }
  return sum;
}

int calc_fuel(int alignment, vector<int>& crabs) {
  int fuel = 0;
  for (size_t i = 0; i < crabs.size(); i++) {
    int n = abs(crabs[i] - alignment);
    fuel += (pow(n, 2) + n) / 2;
  }
  return fuel;
}

int least_fuel(vector<int>& crabs) {
  double mean = (double) sum_vector(crabs) / (double) crabs.size();
  int meanFloor = floor(mean);
  int meanCeil = ceil(mean);
  return min(calc_fuel(meanFloor, crabs), calc_fuel(meanCeil, crabs));
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
