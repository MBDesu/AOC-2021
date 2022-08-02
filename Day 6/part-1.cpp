#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int days_passed = 0;

void print_state(vector<int>& lanternfish) {
  cout << days_passed << ": ";
  for (size_t i = 0; i < lanternfish.size(); i++) {
    if (i < lanternfish.size() - 1) {
      cout << lanternfish.at(i) << ", ";
    } else {
      cout << lanternfish.at(i) << endl;
    }
  }
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

void advance_state(vector<int>& lanternfish) { 
  vector<int> new_fish = {};
  for (size_t i = 0; i < lanternfish.size(); i++) {
    int current_fish = lanternfish.at(i);
    if (lanternfish.at(i) == 0) {
      lanternfish.at(i) = 6;
      new_fish.push_back(8); 
    } else {
      lanternfish.at(i) = current_fish - 1;
    }
  }
  lanternfish.insert(lanternfish.end(), new_fish.begin(), new_fish.end());
  days_passed++;
  // print_state(lanternfish);
}

void advance_state(vector<int>& lanternfish, int days_to_advance) {
  for (int i = 0; i < days_to_advance; i++) {
    advance_state(lanternfish);
  }
}

int parse_file(ifstream& file) {
  vector<int> lanternfish;
  while (!file.eof()) {
    string line;
    getline(file, line);
    vector<string> fish = split(line, ",");
    for (size_t i = 0; i < fish.size(); i++) {
      lanternfish.push_back(stoi(fish[i]));
    }
  }
  advance_state(lanternfish, 80);
  return lanternfish.size();
}

int main() {
  ifstream file("input.txt", ios::in);
  cout << "After " << days_passed << " days, there are " << parse_file(file) << " fish." << endl;
  file.close();
  return 0;
}
