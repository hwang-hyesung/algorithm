#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int solution(vector<vector<int> > maps)
{
    int answer = 0;
    int n = maps.size()-1, m = maps[0].size()-1;
    int dy[]={0,-1,0,1}, dx[]={-1,0,1,0};
    queue<pair<int, int>> q;
    q.push({0,0});
    
    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        
        if(y==n && x==m) break;
        
        for(int i=0;i<4;i++){
            int ny = y + dy[i];
            int nx = x + dx[i];
            
            if(ny < 0 || ny > n || nx < 0 || nx > m || maps[ny][nx] != 1) continue;
            
            maps[ny][nx] = maps[y][x]+1;
            q.push({ny, nx});
        }
        
    }
    answer =  maps[n][m]!=1? maps[n][m] : -1;
    
    return answer;
}