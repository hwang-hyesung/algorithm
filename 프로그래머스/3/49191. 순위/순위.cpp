#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<vector<int>> results) {
    int answer = 0;
    vector<vector<bool>> rank(n+1, vector<bool>(n+1, false));
    for(vector<int> res: results){
        rank[res[0]][res[1]] = true;
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            for(int k = 1; k <= n; k++){
                if(rank[j][i] && rank[i][k])
                    rank[j][k] = true;
            }
        }
    }   
                              
    for(int i = 1; i <= n; i++){
        int cnt = 0; 
        for(int j = 1; j <= n; j++){
            if(rank[i][j] || rank[j][i])
                cnt++; 
        }
        if(cnt == n-1)
            answer++; 
    }    
    
    return answer;
}