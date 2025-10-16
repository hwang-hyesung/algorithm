#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

int solution(int n, vector<vector<int>> computers) {
    int answer = 0, visited[201];
    memset(visited, 0, sizeof(visited));
    map<int, vector<int> > m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(computers[i][j]==1)
                m[i].push_back(j);
        }
    }
    
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i] = ++answer;
            queue<int> q;
            q.push(i);
            while(!q.empty()){
                int next = q.front();
                q.pop();

                for(int net : m[next]){
                    if(visited[net]!=0) continue;
                    q.push(net);
                    visited[net]=answer;
                }
            }
        }
    }
    return answer;
}