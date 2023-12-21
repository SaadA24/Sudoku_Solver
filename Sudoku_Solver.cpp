#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

std::vector<std::vector<int>> split_into_subgrids(std::vector<std::vector<int>> sudoku) {
    std::vector<std::vector<int>> subgrids;
    for (int box_row = 0; box_row < 3; box_row++) {
        for (int box_col = 0; box_col < 3; box_col++) {
            std::vector<int> subgrid;
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    subgrid.push_back(sudoku[3 * box_row + row][3 * box_col + col]);
                }
            }
            subgrids.push_back(subgrid);
        }
    }
    return subgrids;
}

bool is_valid_board(std::vector<std::vector<int>>& sudoku) {
    std::vector<std::vector<int>> subgrids = split_into_subgrids(sudoku);
    for (int i = 0; i < 9; i++) {
        std::vector<int> duplicates_row;
        std::vector<int> duplicates_col;
        std::vector<int> duplicates_3x3;
        std::unordered_map<int, int> counter_row;
        std::unordered_map<int, int> counter_col;
        std::unordered_map<int, int> counter_3x3;
        
        for (int j = 0; j < 9; j++) {
            counter_row[sudoku[i][j]]++;
            counter_col[sudoku[j][i]]++;
            counter_3x3[subgrids[i][j]]++;
        }
        
        for (auto it = counter_row.begin(); it != counter_row.end(); it++) {
            if (it->second > 1) {
                duplicates_row.push_back(it->first);
            }
        }
        
        for (auto it = counter_col.begin(); it != counter_col.end(); it++) {
            if (it->second > 1) {
                duplicates_col.push_back(it->first);
            }
        }
        
        for (auto it = counter_3x3.begin(); it != counter_3x3.end(); it++) {
            if (it->second > 1) {
                duplicates_3x3.push_back(it->first);
            }
        }
        
        if (std::unique(sudoku[i].begin(), sudoku[i].end()) != sudoku[i].end()) {
            if (std::find(duplicates_row.begin(), duplicates_row.end(), 0) != duplicates_row.end()) {
                return true;
            } else {
                return false;
            }
        }
        
        if (std::unique(sudoku[i].begin(), sudoku[i].end()) != sudoku[i].end()) {
            if (std::find(duplicates_col.begin(), duplicates_col.end(), 0) != duplicates_col.end()) {
                return true;
            } else {
                return false;
            }
        }
        
        if (std::unique(subgrids[i].begin(), subgrids[i].end()) != subgrids[i].end()) {
            if (std::find(duplicates_3x3.begin(), duplicates_3x3.end(), 0) != duplicates_3x3.end()) {
                return true;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool is_valid_move(std::vector<std::vector<int>> grid, int row, int col, int n) {
    int s_row = (row / 3) * 3;
    int s_col = (col / 3) * 3;
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == n) {
            return false;
        }
        if (grid[i][col] == n) {
            return false;
        }
        if (grid[s_row + (i / 3)][s_col + (i % 3)] == n) {
            return false;
        }
    }
    return true;
}

std::unordered_set<int> digit_options(const std::array<std::array<int, 9>, 9>& board, int row, int col) {
    int s_row = (row / 3) * 3;
    int s_col = (col / 3) * 3;
    std::unordered_set<int> num;
    for (int i = 1; i <= 9; i++) {
        num.insert(i);
    }
    std::unordered_set<int> used_row_digits;
    for (int i = 0; i < 9; i++) {
        used_row_digits.insert(board[row][i]);
    }
    std::unordered_set<int> used_col_digits;
    for (int i = 0; i < 9; i++) {
        used_col_digits.insert(board[i][col]);
    }
    std::unordered_set<int> used_3x3_digits;
    for (int i = 0; i < 9; i++) {
        used_3x3_digits.insert(board[s_row + (i / 3)][s_col + (i % 3)]);
    }
    std::unordered_set<int> unused_row_digits;
    for (int i = 1; i <= 9; i++) {
        if (used_row_digits.find(i) == used_row_digits.end()) {
            unused_row_digits.insert(i);
        }
    }
    std::unordered_set<int> unused_col_digits;
    for (int i = 1; i <= 9; i++) {
        if (used_col_digits.find(i) == used_col_digits.end()) {
            unused_col_digits.insert(i);
        }
    }
    std::unordered_set<int> unused_3x3_digits;
    for (int i = 1; i <= 9; i++) {
        if (used_3x3_digits.find(i) == used_3x3_digits.end()) {
            unused_3x3_digits.insert(i);
        }
    }
    std::unordered_set<int> options;
    for (int num : unused_col_digits) {
        if (unused_row_digits.find(num) != unused_row_digits.end() && unused_3x3_digits.find(num) != unused_3x3_digits.end()) {
            options.insert(num);
        }
    }
    return options;
}

// type 2

bool is_valid_move(std::array<std::array<int, 9>, 9>& board, int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }
    int s_row = (row / 3) * 3;
    int s_col = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[s_row + i][s_col + j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool make_move(std::array<std::array<int, 9>, 9>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                std::unordered_set<int> options = digit_options(board, row, col);
                for (int num : options) {
                    if (is_valid_move(board, row, col, num)) {
                        board[row][col] = num;
                        if (make_move(board)) {
                            return true;
                        }
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void invalid_board_marker(std::vector<std::vector<int>>& sudoku) {
    for (int i = 0; i < sudoku.size(); i++) {
        for (int j = 0; j < sudoku[i].size(); j++) {
            if (sudoku[i][j] >= 0) {
                sudoku[i][j] = -1;
            }
        }
    }
}

std::vector<std::vector<int>> sudoku_solver(std::vector<std::vector<int>>& sudoku) {
    if (is_valid_board(sudoku)) {
        if (make_move(sudoku)) {
            return sudoku;
        } else {
            invalid_board_marker(sudoku);
            return sudoku;
        }
    } else {
        invalid_board_marker(sudoku);
        return sudoku;
    }
}

int main() {
    // example usage
    std::vector<std::vector<int>> sudoku = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::vector<std::vector<int>> solved_sudoku = sudoku_solver(sudoku);

    // print the solved sudoku
    for (int i = 0; i < solved_sudoku.size(); i++) {
        for (int j = 0; j < solved_sudoku[i].size(); j++) {
            std::cout << solved_sudoku[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
