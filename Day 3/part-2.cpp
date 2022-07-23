#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// this can probably be done in a single pass and iteratively,
// but uh...recursion!
int get_safety_value(vector<string> values, int start_pos, bool is_oxygen) {
  vector<string> new_values(values);
  int counts[2] = { 0, 0 }; // 0, 1
  for (size_t i = 0; i < values.size(); i++) {
    if (values.at(i).at(start_pos) - '0') {
      counts[1]++;
    } else {
      counts[0]++;
    }
  }
  new_values.erase(remove_if(new_values.begin(), new_values.end(), [&](const string & s) {
    char c_to_filter;
    if (is_oxygen) {
      c_to_filter = counts[1] >= counts[0] ? 1 + '0' : 0 + '0';
    } else {
      c_to_filter = counts[1] >= counts[0] ? 0 + '0' : 1 + '0';
    }
    return s.at(start_pos) != c_to_filter;
  }), new_values.end());
  return new_values.size() > 1 ? get_safety_value(new_values, start_pos + 1, is_oxygen) : stoi(new_values.at(0), nullptr, 2);
}

int parse_file(ifstream *file) {
  vector<string> lines;
  for (string line; getline(*file, line);) {
    lines.push_back(line);
  }
  return get_safety_value(lines, 0, true) * get_safety_value(lines, 0, false);
}

int main() {
  ifstream file;
  file.open("input.txt", ifstream::in);
  cout << parse_file(&file) << endl;  
  file.close();
  return 0;
}
