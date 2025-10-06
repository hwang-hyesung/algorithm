#include <bits/stdc++.h>
using namespace std;
int n, k, arr[101], dp[100001], cnt=0;

void go(int num) {
    if(num >= k) return;
    for(int i=0;i<n;i++){
        if(dp[num+arr[i]] <= dp[num]+1) continue;
        dp[num+arr[i]] = dp[num]+1;
        go(num + arr[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> k;
    fill(dp, dp + 10001, 1e9); 
    dp[0] = 0;   
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    go(0);
    if(dp[k] == 1e9) cout << -1 << '\n';
    else cout << dp[k] << '\n';
    return 0;
}
