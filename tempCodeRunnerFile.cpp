
    for (int i = 0; i < 9; i++) {
        used_col_digits.insert(board[i][col]);
    }
    std::unordered_set<int> used_3x3_digits;
    for (int i = 0; i < 9; i++) {
        used_3x3_digits.insert(board[s_row + (i / 3)][s_col + (i % 3)]);