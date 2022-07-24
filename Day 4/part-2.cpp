#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct square {
  int value;
  bool marked = false;
};

struct board {
  int winning_pick;
  vector<vector<square>> rows;
};

void print_board(board *board) {
  for (size_t i = 0; i < board->rows.size(); i++) {
    for (size_t j = 0; j < board->rows.at(i).size(); j++) {
      square square = board->rows.at(i).at(j);
      if (square.marked) {
        cout << "[" << square.value << "] ";
      } else {
        cout << square.value << " ";
      }
    }
    cout << endl;
  }
}

int score_winner(int winning_pick, board *board) {
  int sum_of_unmarked = 0;
  for (size_t i = 0; i < board->rows.size(); i++) {
    for (size_t j = 0; j < board->rows.at(i).size(); j++) {
      if (!board->rows.at(i).at(j).marked) {
        sum_of_unmarked += board->rows.at(i).at(j).value;
      }
    }
  }
  return sum_of_unmarked * winning_pick;
}

bool check_cols(board *board) {
  bool winner = false;
  for (size_t i = 0; i < 5; i++) {
    winner = board->rows.at(0).at(i).marked &&
             board->rows.at(1).at(i).marked &&
             board->rows.at(2).at(i).marked &&
             board->rows.at(3).at(i).marked &&
             board->rows.at(4).at(i).marked;
    if (winner) {
      return winner;
    }
  }
  return winner;
}

bool check_rows(board *board) {
  bool winner = false;
  for (size_t i = 0; i < 5; i++) {
    winner = board->rows.at(i).at(0).marked &&
             board->rows.at(i).at(1).marked &&
             board->rows.at(i).at(2).marked &&
             board->rows.at(i).at(3).marked &&
             board->rows.at(i).at(4).marked;
    if (winner) {
      return winner;
    }
  }
  return winner;
}

bool is_winner(board board) {
  return check_rows(&board) || check_cols(&board);
}

void check_winners(int winning_pick, vector<board> *boards, vector<board> *winners) {
  for (size_t i = 0; i < boards->size(); i++) {
    if (is_winner(boards->at(i))) {
      boards->at(i).winning_pick = winning_pick;
      winners->push_back(boards->at(i));
      boards->erase(boards->begin() + i);
    }
  }
}

void mark_boards(vector<int> *picks, vector<board> *boards, vector<board> *winners) {
  // good lord, there is definitely a better way
  // but I bet it would require refactoring structs
  for (size_t i = 0; i < picks->size(); i++) {
    for (size_t j = 0; j < boards->size(); j++) {
      for (size_t k = 0; k < boards->at(j).rows.size(); k++) {
        for (size_t l = 0; l < boards->at(j).rows.at(k).size(); l++) {
          int value = boards->at(j).rows.at(k).at(l).value;
          if (picks->at(i) == value) {
            boards->at(j).rows.at(k).at(l).marked = true;
          }
        }
      }
    }
    check_winners(picks->at(i), boards, winners);
  }
}

void parse_board_row(ifstream *file, vector<square> *row) {
  string value_s;
  string line;
  getline(*file, line);
  istringstream iss(line);
  for (string value_s; iss >> value_s;) {
    square square;
    square.value = stoi(value_s);
    row->push_back(square);
  }
}

void parse_board(ifstream *file, vector<board> *boards) {
  board board;
  for (size_t i = 0; i < 5; i++) {
    vector<square> row;
    parse_board_row(file, &row);
    board.rows.push_back(row);
  }
  boards->push_back(board);
  string dummy;
  getline(*file, dummy); // clear blank line
}

void parse_boards(ifstream *file, vector<board> *boards) {
  while(!file->eof()) {
    parse_board(file, boards);
  }
}

void parse_picks(ifstream *file, vector<int> *picks) {
  string pick_s;
  string line;
  getline(*file, line);
  stringstream ss(line);
  while (getline(ss, pick_s, ',')) {
    picks->push_back(stoi(pick_s));
  }
  getline(*file, line); // clear blank line
}

int parse_file(ifstream *file) {
  vector<board> boards;
  vector<board> winners;
  vector<int> picks;
  parse_picks(file, &picks);
  parse_boards(file, &boards);
  mark_boards(&picks, &boards, &winners);
  int last_winner_index = winners.size() - 1;
  int winning_pick = winners.at(last_winner_index).winning_pick;
  return score_winner(winning_pick, &winners.at(last_winner_index));
}

int main() {
  ifstream file;
  file.open("input.txt", ifstream::in);
  cout << parse_file(&file) << endl;
  file.close();
  return 0;
}
