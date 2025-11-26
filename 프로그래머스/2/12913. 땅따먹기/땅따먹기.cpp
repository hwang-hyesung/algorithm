#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int solution(vector<vector<int> > land)
{
    int answer = 0, lsize = land.size();
    vector<vector<int>> sum(lsize, vector<int>(4, 0));
    
    for(int j=0;j<4;j++){
        sum[0][j] = land[0][j];
    }
    
    for(int i=1;i<lsize;i++){
        int ans = 0;
        for(int j=0;j<4;j++){
            int msum = 0;
            for(int k=0;k<4;k++){
                if(k==j) continue;
                if(msum < sum[i-1][k] + land[i][j]) msum = sum[i-1][k] + land[i][j];
            }
            sum[i][j] = msum;
            if(i==lsize-1 && ans < msum) ans = msum;
        }
        answer = ans;
    }    

    return answer;
}