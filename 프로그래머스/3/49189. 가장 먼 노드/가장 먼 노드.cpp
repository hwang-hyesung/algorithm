#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    vector<vector<int>> adj(n+1);
    for(vector<int> e : edge){
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    
    int answer = 0, arr[20005], mx = 0;
    memset(arr, 0, sizeof(arr));
    queue<pair<int, int> > q;
    map<int, int> m;
    q.push({1,0});
    arr[1] = 1;
    
    while(!q.empty()){
        int node = q.front().first;
        int dis = q.front().second;
        q.pop();
        
        for(int e : adj[node]){
            if(arr[e]!=0) continue;
            q.push({e, dis+1});
            arr[e] = dis+1;
            m[dis+1]++;
            mx = max(mx, dis+1);
        }
    }
    
    return m[mx];
}