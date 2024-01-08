#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

// Split Sudoku board into 3x3 subgrads from left to right

std::vector<std::vector<int>> splitSudokuBoardIntoSubgrids(const std::vector<std::vector<int>>& sudokuBoard) {

    std::vector<std::vector<int>> allSubgrids;
    std::vector<int> eachSubgrid;

    for (int allSubgridBoxRows = 0; allSubgridBoxRows < 3; allSubgridBoxRows++) {
        for (int allsubgridBoxColumns = 0; allsubgridBoxColumns < 3; allsubgridBoxColumns++) {
            for (int eachSubgridRow = 0; eachSubgridRow < 3; eachSubgridRow++) {
                for (int eachSubgrodColumn = 0; eachSubgrodColumn < 3; eachSubgrodColumn++) {
                    eachSubgrid.push_back(sudokuBoard[3 * allSubgridBoxRows + eachSubgridRow][3 * allsubgridBoxColumns + eachSubgrodColumn]);
                }
            }
            allSubgrids.push_back(eachSubgrid);
        }
    }
    return allSubgrids;
}

// Check duplicates in the board that break the Sudoku rules

bool checkDuplicates(std::vector<std::vector<int>>& sudokuBoard) {

    std::vector<int> subGridRowDuplicates;
    std::vector<int> subGridColumnDuplicates;
    std::vector<int> individualSubGridDuplicates;
    std::unordered_map<int, int> eachSubGridRow;
    std::unordered_map<int, int> eachSubGridColumn;
    std::unordered_map<int, int> eachIndividualSubGrid;

    std::vector<std::vector<int>> eachSubGrid = splitSudokuBoardIntoSubgrids(sudokuBoard);

    //Loop through each board row, board column and 3x3 subgrid
    for (int i = 0; i < 9; i++) {
        
        // Count occurrences of numbers in each subGridrow, subGridColumn, and 3x3 subgrid
        for (int j = 0; j < 9; j++) {
            eachSubGridRow[sudokuBoard[i][j]]++;
            eachSubGridColumn[sudokuBoard[j][i]]++;
            eachIndividualSubGrid[eachSubGrid[i][j]]++;
        }

        // Identify duplicates in the current row
        for (auto iterator = eachSubGridRow.begin(); iterator != eachSubGridRow.end(); iterator++) {
            if (iterator->second > 1) {
                subGridRowDuplicates.push_back(iterator->first);
            }
        }

        // Identify duplicates in the current column
        for (auto iterator = eachSubGridColumn.begin(); iterator != eachSubGridColumn.end(); iterator++) {
            if (iterator->second > 1) {
                subGridColumnDuplicates.push_back(iterator->first);
            }
        }

        // Identify duplicates in the current 3x3 subgrid
        for (auto iterator = eachIndividualSubGrid.begin(); iterator != eachIndividualSubGrid.end(); iterator++) {
            if (iterator->second > 1) {
                individualSubGridDuplicates.push_back(iterator->first);
            }
        }

        // Check rows for duplicates
        if (std::unique(sudokuBoard[i].begin(), sudokuBoard[i].end()) != sudokuBoard[i].end()) {
            if (std::find(subGridRowDuplicates.begin(), subGridRowDuplicates.end(), 0) != subGridRowDuplicates.end()) {
                return true;
            } else {
                return false;
            }
        }
        
        // check columns for duplicates
        if (std::unique(sudokuBoard[i].begin(), sudokuBoard[i].end()) != sudokuBoard[i].end()) {
            if (std::find(subGridColumnDuplicates.begin(), subGridColumnDuplicates.end(), 0) != subGridColumnDuplicates.end()) {
                return true;
            } else {
                return false;
            }
        }

        // check 3x3 for duplicates
        if (std::unique(eachSubGrid[i].begin(), eachSubGrid[i].end()) != eachSubGrid[i].end()) {
            if (std::find(individualSubGridDuplicates.begin(), individualSubGridDuplicates.end(), 0) != individualSubGridDuplicates.end()) {
                return true;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool subGridValidGuess(std::vector<std::vector<int>> eachSubgrid, int subGridRow, int subGridColumn, int subGridInputGuess) {
    int allSudokuBoardRows = (subGridRow / 3) * 3;
    int allSudokuBoardColumns = (subGridColumn / 3) * 3;
    for (int i = 0; i < 9; i++) {
        if (eachSubgrid[subGridRow][i] == subGridInputGuess) {
            return false;
        }
        if (eachSubgrid[i][subGridColumn] == subGridInputGuess) {
            return false;
        }
        if (eachSubgrid[subGridRow + (i / 3)][subGridColumn + (i % 3)] == subGridInputGuess) {
            return false;
        }
    }
    return true;
}

bool sudokoBoardValidGuess(const std::array<std::array<int, 9>, 9>& sudokuBoard, int sudokuBoardRow, int sudokuBoardColumn, int SudokuBoardInputGuess) {
    for (int i = 0; i < 9; i++) {
        if (sudokuBoard[sudokuBoardRow][i] == SudokuBoardInputGuess || sudokuBoard[i][sudokuBoardColumn] == SudokuBoardInputGuess) {
            return false;
        }
    }
    int allSudokuBoardRows = (sudokuBoardRow / 3) * 3;
    int allSudokuBoardColumns = (sudokuBoardColumn / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudokuBoard[allSudokuBoardRows + i][allSudokuBoardColumns + j] == SudokuBoardInputGuess) {
                return false;
            }
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
    if (checkDuplicates(sudoku)) {
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
