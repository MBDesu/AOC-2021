#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct point {
  int x;
  int y;
  int height;
  bool visited = false;
};

bool is_low_point(int x, std::vector<point>& adjacencies) {
  for (size_t i = 0; i < adjacencies.size(); i++) {
    if (adjacencies[i].height <= x) {
      return false;
    }
  }
  return true;
}

void clear_visited_state(std::vector<std::vector<point>>& grid) {
  for (size_t i = 0; i < grid.size(); i++) {
    for (size_t j = 0; j < grid[i].size(); j++) {
      grid[i][j].visited = false;
    }
  }
}

int pop_largest(std::vector<int>& basin_sizes) {
  int largest = 0;
  int largest_index = 0;
  for (size_t i = 0; i < basin_sizes.size(); i++) {
    if (basin_sizes[i] > largest) {
      largest = basin_sizes[i];
      largest_index = i;
    }
  }
  basin_sizes.erase(basin_sizes.begin() + largest_index, basin_sizes.begin() + largest_index + 1);
  return largest;
}

int calculate_result(std::vector<int> basin_sizes) {
  return pop_largest(basin_sizes) * pop_largest(basin_sizes) * pop_largest(basin_sizes);
}

// don't look at this
void find_basin_adjacencies(std::vector<std::vector<point>>& grid, point& p, std::vector<point>& basin_adjacencies) {
  int x = p.x;
  int y = p.y;
  p.visited = true;
  if (y == 0 && grid[y + 1][x].height != 9 && grid[y + 1][x].height > p.height && !grid[y + 1][x].visited) {
    basin_adjacencies.push_back(grid[y + 1][x]);
    find_basin_adjacencies(grid, grid[y + 1][x], basin_adjacencies);
  } else if (y == grid.size() - 1 && grid[y - 1][x].height > p.height && grid[y - 1][x].height != 9 && !grid[y - 1][x].visited) {
    basin_adjacencies.push_back(grid[y - 1][x]);
    find_basin_adjacencies(grid, grid[y - 1][x], basin_adjacencies);
  } else {
    if (y - 1 > 0 && grid[y - 1][x].height > p.height && grid[y - 1][x].height != 9 && !grid[y - 1][x].visited) {
      basin_adjacencies.push_back(grid[y - 1][x]);
      find_basin_adjacencies(grid, grid[y - 1][x], basin_adjacencies);
    }
    if (y + 1 < grid.size() && grid[y + 1][x].height > p.height && grid[y + 1][x].height != 9 && !grid[y + 1][x].visited) {
      basin_adjacencies.push_back(grid[y + 1][x]);
      find_basin_adjacencies(grid, grid[y + 1][x], basin_adjacencies);
    }
  }
  if (x == 0 && grid[y][x + 1].height > p.height && grid[y][x + 1].height != 9 && !grid[y][x + 1].visited) {
    basin_adjacencies.push_back(grid[y][x + 1]);
    find_basin_adjacencies(grid, grid[y][x + 1], basin_adjacencies);
  } else if (x == grid[y].size() - 1 && grid[y][x - 1].height > p.height && grid[y][x - 1].height != 9 && !grid[y][x - 1].visited) {
    basin_adjacencies.push_back(grid[y][x - 1]);
    find_basin_adjacencies(grid, grid[y][x - 1], basin_adjacencies);
  } else {
    if (grid[y][x - 1].height > p.height && grid[y][x - 1].height != 9 && !grid[y][x - 1].visited) {
      basin_adjacencies.push_back(grid[y][x - 1]);
      find_basin_adjacencies(grid, grid[y][x - 1], basin_adjacencies);
    }
    if (grid[y][x + 1].height > p.height && grid[y][x + 1].height != 9 && !grid[y][x + 1].visited) {
      basin_adjacencies.push_back(grid[y][x + 1]);
      find_basin_adjacencies(grid, grid[y][x + 1], basin_adjacencies);
    }
  }
}

void find_low_points(std::vector<std::vector<point>>& grid, std::vector<point>& low_points) {
  for (size_t y = 0; y < grid.size(); y++) {
    for (size_t x = 0; x < grid[y].size(); x++) {
      std::vector<point> adjacencies;
      if (y == 0) {
        adjacencies.push_back(grid[y + 1][x]);
      } else if (y == grid.size() - 1) {
        adjacencies.push_back(grid[y - 1][x]);
      } else {
        adjacencies.push_back(grid[y - 1][x]);
        adjacencies.push_back(grid[y + 1][x]);
      }
      if (x == 0) {
        adjacencies.push_back(grid[y][x + 1]);
      } else if (x == grid[y].size() - 1) {
        adjacencies.push_back(grid[y][x - 1]);
      } else {
        adjacencies.push_back(grid[y][x - 1]);
        adjacencies.push_back(grid[y][x + 1]);
      }
      if (is_low_point(grid[y][x].height, adjacencies)) {
        low_points.push_back(grid[y][x]);
      }
    }
  }
}

int parse_file(std::ifstream& file) {
  std::vector<std::vector<point>> grid;
  std::vector<point> low_points;
  std::vector<int> basin_sizes;
  int x = 0;
  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    std::vector<point> row;
    for (int i = 0; i < line.size(); i++) {
      row.push_back(point{ i, x, line[i] - '0' });
    }
    grid.push_back(row);
    x++;
  }
  find_low_points(grid, low_points);
  for (size_t i = 0; i < low_points.size(); i++) {
    std::vector<point> basin;
    basin.push_back(low_points[i]);
    find_basin_adjacencies(grid, low_points[i], basin);
    basin_sizes.push_back(basin.size());
    clear_visited_state(grid);
  }
  return calculate_result(basin_sizes);
}

int main() {
  std::ifstream file("input.txt", std::ios::in);
  std::cout << parse_file(file) << std::endl;
  file.close();
  return 0;
}
