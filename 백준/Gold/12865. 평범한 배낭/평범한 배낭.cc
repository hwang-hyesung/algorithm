#include <bits/stdc++.h>
using namespace std;
int n, k, w, v;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    int dp[k+1];
    fill(dp, dp+k+1, 0);
    for(int i=0;i<n;i++){
        cin >> w >> v;    
        for(int j = k; j >= w; j--){
            dp[j] = max(dp[j], dp[j-w] + v);
        }
    }
    cout << dp[k] << '\n';

    return 0;
}
