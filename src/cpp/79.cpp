class Solution {
public:
    int rows, cols, n;

    bool dfs(vector<vector<char>>& board, string& word, int row, int col, int& count) {
        if (count == n) return true;

        if (row < 0 || row == rows || col < 0 || col == cols) return false;
        if (board[row][col] != word[count]) return false;

        board[row][col] -= 64;
        ++count;

        bool check = dfs(board, word, row, col + 1, count)
                  || dfs(board, word, row + 1, col, count)
                  || dfs(board, word, row, col - 1, count)
                  || dfs(board, word, row - 1, col, count);

        --count;
        board[row][col] += 64;

        return check;
    }

    bool exist(vector<vector<char>>& board, string& word) {
        rows = board.size();
        cols = board[0].size();
        n = word.size();

        // Pruning 1: Return false if the length of 
        // the given word is larger than the board size
        if (n > rows * cols) return false;

        
        int freq[123] {};
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ++freq[board[i][j]];
            }
        }

        // Pruning 2: Returns true if the length of the given word
        // is 1 and its only character appears in the board
        if (n == 1 && freq[word[0]] > 0) return true;

        // Pruning 3: Return false if the freq of any character in
        // the given word is greater than its freq in the table
        for (int i = 0; i < n; i++) {
            if (--freq[word[i]] < 0) {
                return false;
            }
        }

        // Pruning 4: Reverse the given word if
        // its prefix is longer than its suffix
        int left = 0, right = n - 1;

        while (left < right) {
            if (word[left] != word[++left] && word[right] == word[--right]) {
                reverse(word.begin(), word.end());
                break;
            }
        }

        // DFS
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (dfs(board, word, i, j, count) == true) {
                    return true;
                }
            }
        }

        return false;
    }
};