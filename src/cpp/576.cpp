#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

static const bool __boost = [](){
    cin.tie(nullptr);
    cout.tie(nullptr);
    return ios_base::sync_with_stdio(false);
}();

#define MOD 1000000007

class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        if (!maxMove) return 0;
        if (m == 1 && n == 1) return 4;

        // Current grid
        vector<vector<int>> dp(m, vector<int>(n));
        dp[startRow][startColumn] = 1;

        // Next grid
        vector<vector<int>> dp1(m);

        int count = 0;

        while (maxMove-->0) {
            fill(dp1.begin(), dp1.end(), vector<int>(n));

            // Corners
            count += (dp[0][0] * 2) % MOD; count %= MOD;

            if (m > 1) {
                count += dp[m - 1][0] % MOD; count %= MOD;

                dp1[0][0] = dp[1][0];
                dp1[m - 1][0] = dp[m - 2][0];
            }
            count += dp[m - 1][0] % MOD; count %= MOD;

            if (n > 1) {
                count += dp[0][n - 1] % MOD; count %= MOD;

                dp1[0][0] += dp[0][1]; dp1[0][0] %= MOD;
                dp1[0][n - 1] = dp[0][n - 2];
            }
            count += dp[0][n - 1] % MOD; count %= MOD;

            if (m > 1 && n > 1) {
                count += dp[m - 1][n - 1] % MOD; count %= MOD;

                dp1[m - 1][n - 1] = (dp[m - 1][n - 2] + dp[m - 2][n - 1]);
                dp1[m - 1][n - 1] %= MOD;

                dp1[0][n - 1] += dp[1][n - 1]; dp1[0][n - 1] %= MOD;
                dp1[m - 1][0] += dp[m - 1][1]; dp1[m - 1][0] %= MOD;
            }
            count += dp[m - 1][n - 1]; count %= MOD;

            // Vertical edges
            for (int j = 1; j < n - 1; ++j) {
                count += dp[0][j]; count %= MOD;
                count += dp[m - 1][j]; count %= MOD;

                dp1[0][j] = (dp[0][j - 1] + dp[0][j + 1]) % MOD;

                if (m > 1) {
                    dp1[0][j] += dp[1][j]; dp1[0][j] %= MOD;

                    dp1[m - 1][j] = dp[m - 1][j - 1] + dp[m - 1][j + 1];
                    dp1[m - 1][j] %= MOD;
                    dp1[m - 1][j] += dp[m - 2][j];
                    dp1[m - 1][j] %= MOD;
                }
            }

            // Horizontal edges
            for (int i = 1; i < m - 1; ++i) {
                count += dp[i][0]; count %= MOD;
                count += dp[i][n - 1]; count %= MOD;

                dp1[i][0] = (dp[i - 1][0] + dp[i + 1][0]) % MOD;

                if (n > 1) {
                    dp1[i][0] += dp[i][1]; dp1[i][0] %= MOD;

                    dp1[i][n - 1] = dp[i - 1][n - 1] + dp[i + 1][n - 1];
                    dp1[i][n - 1] %= MOD;
                    dp1[i][n - 1] += dp[i][n - 2];
                    dp1[i][n - 1] %= MOD;
                }
            }

            // Inside
            for (int i = 1; i < m - 1; ++i) {
                for (int j = 1; j < n - 1; ++j) {
                    dp1[i][j] = (dp[i - 1][j] + dp[i + 1][j]) % MOD;
                    dp1[i][j] += (dp[i][j - 1] + dp[i][j + 1]) % MOD;
                    dp1[i][j] %= MOD;
                }
            }

            swap(dp, dp1);
        }

        return count;
    }
};