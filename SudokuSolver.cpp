#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>

// Split Sudoku board into 3x3 subgrads from left to right

std::vector<std::vector<int>> splitSudokuBoardIntoSubgrids(std::array<std::array<int, 9>, 9>& sudokuBoard) {

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

bool checkDuplicates(std::array<std::array<int, 9>, 9>& sudokuBoard) {

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

// Reject invalid guesses for existing numbers in eachSubGrid

bool checkValidGuess(std::array<std::array<int, 9>, 9>& eachSubgrid, int subGridRow, int subGridColumn, int subGridInputGuess) {
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

std::unordered_set<int> digitOptionsForGuesses(const std::array<std::array<int, 9>, 9>& sudokuBoard, int sudokuBoardRow, int sudokuBoardColumn) {

    int eachSubgridRow = (sudokuBoardRow / 3) * 3;
    int eachSubGridColumn = (sudokuBoardColumn / 3) * 3;

    std::unordered_set<int> num;
    for (int i = 1; i <= 9; i++) {
        num.insert(i);
    }
    std::unordered_set<int> usedSudokuBoardRowDigits;
    for (int i = 0; i < 9; i++) {
        usedSudokuBoardRowDigits.insert(sudokuBoard[sudokuBoardRow][i]);
    }
    std::unordered_set<int> usedSudokuBoardColumnDigits;
    for (int i = 0; i < 9; i++) {
        usedSudokuBoardColumnDigits.insert(sudokuBoard[i][sudokuBoardColumn]);
    }
    std::unordered_set<int> usedEachSubgridDigits;
    for (int i = 0; i < 9; i++) {
        usedEachSubgridDigits.insert(sudokuBoard[eachSubgridRow + (i / 3)][eachSubGridColumn + (i % 3)]);
    }
    std::unordered_set<int> unUsedSudokuBoardRowDigits;
    for (int i = 1; i <= 9; i++) {
        if (usedSudokuBoardRowDigits.find(i) == usedSudokuBoardRowDigits.end()) {
            unUsedSudokuBoardRowDigits.insert(i);
        }
    }
    std::unordered_set<int> unUsedSudokuBoardColumnDigits;
    for (int i = 1; i <= 9; i++) {
        if (usedSudokuBoardColumnDigits.find(i) == usedSudokuBoardColumnDigits.end()) {
            unUsedSudokuBoardColumnDigits.insert(i);
        }
    }
    std::unordered_set<int> unUsedEachSubgridDigits;
    for (int i = 1; i <= 9; i++) {
        if (usedEachSubgridDigits.find(i) == usedEachSubgridDigits.end()) {
            unUsedEachSubgridDigits.insert(i);
        }
    }
    std::unordered_set<int> options;
    for (int guess : unUsedSudokuBoardColumnDigits) {
        if (unUsedSudokuBoardRowDigits.find(guess) != unUsedSudokuBoardRowDigits.end() && unUsedEachSubgridDigits.find(guess) != unUsedEachSubgridDigits.end()) {
            options.insert(guess);
        }
    }
    return options;
}

// to do

bool insertGuess(std::array<std::array<int, 9>, 9>& sudokuBoard) {
    for (int sudokuBoardRow = 0; sudokuBoardRow < 9; sudokuBoardRow++) {
        for (int sudokuBoardColumn = 0; sudokuBoardColumn < 9; sudokuBoardColumn++) {
            if (sudokuBoard[sudokuBoardRow][sudokuBoardRow] == 0) {
                std::unordered_set<int> guessOptions = digitOptionsForGuesses(sudokuBoard, sudokuBoardRow, sudokuBoardColumn);
                for (int guess : guessOptions) {
                    if (checkValidGuess(sudokuBoard, sudokuBoardRow, sudokuBoardColumn, guess)) {
                        sudokuBoard[sudokuBoardRow][sudokuBoardColumn] = guess;
                        if (insertGuess(sudokuBoard)) {
                            return true;
                        }
                        sudokuBoard[sudokuBoardRow][sudokuBoardColumn] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// If number exists, set it to -1 to ignore

void invalid_board_marker(std::array<std::array<int, 9>, 9>& sudokuBoard) {
    for (int i = 0; i < sudokuBoard.size(); i++) {
        for (int j = 0; j < sudokuBoard[i].size(); j++) {
            if (sudokuBoard[i][j] >= 0) {
                sudokuBoard[i][j] = -1;
            }
        }
    }
}

std::array<std::array<int, 9>, 9> sudokuSolver(std::array<std::array<int, 9>, 9> sudokuBoard) {
    if (checkDuplicates(sudokuBoard)) {
        if (insertGuess(sudokuBoard)) {
            return sudokuBoard;
        } else {
            invalid_board_marker(sudokuBoard);
            return sudokuBoard;
        }
    } else {
        invalid_board_marker(sudokuBoard);
        return sudokuBoard;
    }
}

int main() {
    
    // example usage
    std::array<std::array<int, 9>, 9> sudokuBoardExample = {{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
}};

    std::array<std::array<int, 9>, 9> solvedSudokuBoardExample = sudokuSolver(sudokuBoardExample);

    // print the solved sudoku
    for (int i = 0; i < solvedSudokuBoardExample.size(); i++) {
        for (int j = 0; j < solvedSudokuBoardExample[i].size(); j++) {
            std::cout << solvedSudokuBoardExample[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
