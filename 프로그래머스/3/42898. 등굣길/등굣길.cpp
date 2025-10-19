#include <string>
#include <vector>

using namespace std;

int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    vector<vector<int>> road(n, vector<int>(m, 0));
    
    for(vector<int> p : puddles){
        road[p[1]-1][p[0]-1] = -1;
    }
    
    road[0][0] = 1;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(road[i][j]==-1) {
                road[i][j] = 0;
                continue;
            }
            
            if(i!=0)
                road[i][j] += road[i-1][j];
            if(j!=0)
                road[i][j] += road[i][j-1];
            
            road[i][j] %= 1000000007; 
        }
    }
    
    answer = road[n-1][m-1] % 1000000007;
    return answer;
}