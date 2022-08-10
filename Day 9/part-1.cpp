#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void print_int_vector(std::vector<int>& v) {
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

void print_grid(std::vector<std::vector<int>>& grid) {
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int calculate_risk_level(std::vector<int>& low_points) {
  int risk_level = 0;
  for (size_t i = 0; i < low_points.size(); i++) {
    risk_level += low_points[i] + 1;
  }
  return risk_level;
}

bool is_low_point(int x, std::vector<int>& adjacencies) {
  for (size_t i = 0; i < adjacencies.size(); i++) {
    if (adjacencies[i] <= x) {
      return false;
    }
  }
  return true;
}

void find_low_points(std::vector<std::vector<int>>& grid, std::vector<int>& low_points) {
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      std::vector<int> adjacencies;
      if (i == 0) {
        adjacencies.push_back(grid[i + 1][j]);
      } else if (i == grid.size() - 1) {
        adjacencies.push_back(grid[i - 1][j]);
      } else {
        adjacencies.push_back(grid[i - 1][j]);
        adjacencies.push_back(grid[i + 1][j]);
      }
      if (j == 0) {
        adjacencies.push_back(grid[i][j + 1]);
      } else if (j == grid[i].size() - 1) {
        adjacencies.push_back(grid[i][j - 1]);
      } else {
        adjacencies.push_back(grid[i][j - 1]);
        adjacencies.push_back(grid[i][j + 1]);
      }
      if (is_low_point(grid[i][j], adjacencies)) {
        low_points.push_back(grid[i][j]);
      }
    }
  }
}

int parse_file(std::ifstream& file) {
  std::vector<std::vector<int>> grid;
  std::vector<int> low_points;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    std::vector<int> row;
    for (int i = 0; i < line.size(); i++) {
      row.push_back(std::stoi(line.substr(i, 1)));
    }
    grid.push_back(row);
  }
  find_low_points(grid, low_points);
  // print_grid(grid);
  // print_int_vector(low_points);
  return calculate_risk_level(low_points);
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
