#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> info, int n, int m) {
    const int INF = 1e9;
    int sz = info.size();
    vector<vector<int>> dp(sz + 1, vector<int>(m, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= sz; i++) {
        int a = info[i-1][0];
        int b = info[i-1][1];
        for (int j = 0; j < m; j++) {
            if (dp[i-1][j] == INF) continue;
            if (dp[i-1][j] + a < n)
                dp[i][j] = min(dp[i][j], dp[i-1][j] + a);
            if (j + b < m)
                dp[i][j + b] = min(dp[i][j + b], dp[i-1][j]);
        }
    }

    int ans = INF;
    for (int j = 0; j < m; j++) ans = min(ans, dp[sz][j]);
    return ans == INF ? -1 : ans;
}
