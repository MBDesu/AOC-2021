#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int days_passed = 0;

void print_state(vector<unsigned long long int>& lanternfish) {
  cout << days_passed << ": ";
  for (size_t i = 0; i < lanternfish.size(); i++) {
    if (i < lanternfish.size() - 1) {
      cout << lanternfish.at(i) << ",";
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

void advance_state(vector<unsigned long long int>& lanternfish) {
  vector<unsigned long long int> new_lanternfish = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (size_t timer = lanternfish.size() - 1; timer >= 0; --timer) {
    unsigned long long int current_num_fish = lanternfish.at(timer);
    if (timer == 0) {
      new_lanternfish.at(8) += current_num_fish;
      new_lanternfish.at(6) += current_num_fish;
      break;
    } else {
      new_lanternfish.at(timer - 1) += current_num_fish;
    }
  }
  lanternfish = new_lanternfish;
  days_passed++;
  // print_state(lanternfish);
}

void advance_state(vector<unsigned long long int>& lanternfish, int days_to_advance) {
  for (size_t i = 0; i < days_to_advance; i++) {
    advance_state(lanternfish);
  }
}

void set_initial_state(vector<unsigned long long int>& lanternfish) {
  vector<unsigned long long int> new_lanternfish = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (size_t i = 0; i < lanternfish.size(); i++) {
    unsigned long long int current_fish = new_lanternfish.at(lanternfish.at(i));
    new_lanternfish.at(lanternfish.at(i)) = current_fish + 1;
  }
  lanternfish = new_lanternfish;
}

unsigned long long int count_fish(vector<unsigned long long int>& lanternfish) {
  unsigned long long int sum = 0;
  for (size_t i = 0; i < lanternfish.size(); i++) {
    sum += lanternfish.at(i);
  }
  return sum;
}

unsigned long long int parse_file(ifstream& file) {
  vector<unsigned long long int> lanternfish;
  while (!file.eof()) {
    string line;
    getline(file, line);
    vector<string> fish = split(line, ",");
    for (size_t i = 0; i < fish.size(); i++) {
      lanternfish.push_back(stoi(fish[i]));
    }
  }
  set_initial_state(lanternfish);
  advance_state(lanternfish, 256);
  return count_fish(lanternfish);
}

int main() {
  ifstream file("input.txt", ios::in);
  cout << "After " << days_passed << " days, there are " << parse_file(file) << " fish." << endl;
  file.close();
  return 0;
}
