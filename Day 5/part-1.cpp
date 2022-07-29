#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct line {
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;
};

struct point {
  int times_visited = 0;
};

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int find_num_intersections(vector<vector<point>>& grid) {
  int num_intersections = 0;
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      if (grid[i][j].times_visited > 1) {
        num_intersections++;
      }
    }
  }
  return num_intersections;
}

void populate_grid(vector<vector<point>>& grid, vector<line>& lines) {
  for (size_t i = 0; i < lines.size(); i++) {
    int x1 = lines.at(i).x1;
    int x2 = lines.at(i).x2;
    int y1 = lines.at(i).y1;
    int y2 = lines.at(i).y2;
    if (x1 == x2) {
      for (size_t j = min(y2, y1); j <= max(y2, y1); j++) {
        grid.at(j).at(x1).times_visited += 1;
      }
    } else if (y1 == y2) {
      for (size_t j = min(x2, x1); j <= max(x2, x1); j++) {
        grid.at(y1).at(j).times_visited += 1;
      }
    }
  }
}

void construct_grid(vector<vector<point>>& grid, int width, int height) {
  for (size_t i = 0; i <= height; i++) {
    vector<point> row;
    for (size_t j = 0; j <= width; j++) {
      row.push_back(point{0});
    }
    grid.push_back(row);
  }
}

void print_grid(vector<vector<point>>& grid) {
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      int times_visited = grid[i][j].times_visited;
      if (times_visited > 0) {
        cout << times_visited << " ";
      } else {
        cout << "." << " ";
      }
    }
    cout << endl;
  }
}

void print_lines(vector<line>& lines) {
  for (size_t i = 0; i < lines.size(); i++) {
    cout << lines[i].x1 << "," << lines[i].y1 << " -> " << lines[i].x2 << "," << lines[i].y2 << endl;
  }
}

int find_max(vector<line>& lines, bool is_y) {
  int max_val = 0;
  for (size_t i = 0; i < lines.size(); i++) {
    if (is_y) {
      max_val = max(max_val, max(lines[i].y1, lines[i].y2));
    } else {
      max_val = max(max_val, max(lines[i].x1, lines[i].x2));
    }
  }
  return max_val;
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

void parse_line(ifstream& file, vector<line>& lines) {
  string text;
  getline(file, text);
  string start = split(text, " ->")[0];
  string end = split(text, "-> ")[1];
  int x1 = stoi(split(start, ",")[0]);
  int y1 = stoi(split(start, ",")[1]);
  int x2 = stoi(split(end, ",")[0]);
  int y2 = stoi(split(end, ",")[1]);
  lines.push_back(line{x1, x2, y1, y2});
}

int parse_file(ifstream& file) {
  vector<line> lines;
  vector<vector<point>> grid;
  while (!file.eof()) {
    parse_line(file, lines);
  }
  // print_lines(lines);
  int max_x = find_max(lines, false);
  int max_y = find_max(lines, true);
  construct_grid(grid, max_x, max_y);
  populate_grid(grid, lines);
  // print_grid(grid);
  return find_num_intersections(grid);
}

int main() {
  ifstream file;
  file.open("input.txt", ifstream::in);
  cout << parse_file(file) << endl;
  file.close();
  return 0;
}
