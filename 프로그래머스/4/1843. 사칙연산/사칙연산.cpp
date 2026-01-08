#include <vector>
#include <string>
using namespace std;

int solution(vector<string> arr)
{
    int n=(arr.size()+1)/2;
    vector<vector<pair<int,int>>> dp(n,vector<pair<int,int>>(n,{0,0}));

    for(int k=1;k<=n;k++){
        for(int i=0;i<=n-k;i++){ 
            if(k==1){
                dp[i][i].first=stoi(arr[2*i]);
                dp[i][i].second=stoi(arr[2*i]);
            }
            else{
                int min_v=2100000000;
                int max_v=-2100000000;
                int end_i=i+k-2;
                for(int j=i;j<=end_i;j++){
                    if(arr[2*j+1]=="+"){
                        max_v=max(max_v,dp[i][j].second+dp[j+1][i+k-1].second);
                        min_v=min(min_v,dp[i][j].first+dp[j+1][i+k-1].first);
                    }
                    else{
                        max_v=max(max_v,dp[i][j].second-dp[j+1][i+k-1].first);
                        min_v=min(min_v,dp[i][j].first-dp[j+1][i+k-1].second);
                    }
                }
                dp[i][i+k-1].first=min_v;
                dp[i][i+k-1].second=max_v;
            }
        }
    }

    return dp[0][n-1].second;
}