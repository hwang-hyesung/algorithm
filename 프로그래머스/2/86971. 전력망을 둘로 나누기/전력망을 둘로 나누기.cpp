#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int find(int node1, int node2, map<int, vector<int>> &m, int n)
{
    vector<bool> visited(n, false);
    
    int cnt1 = 1, cnt2 = 1;
    visited[node1] = true;
    visited[node2] = true;
    
    queue<int> q1, q2;
    q1.push(node1);
    while(!q1.empty()){
        int node = q1.front();
        q1.pop();
        
        for(int newnode : m[node]){
            if(visited[newnode]) continue;
            cnt1++;
            visited[newnode] = true;
            q1.push(newnode);
        }
    }
    
    q2.push(node2);
    while(!q2.empty()){
        int node = q2.front();
        q2.pop();
        
        for(int newnode : m[node]){
            if(visited[newnode]) continue;
            cnt2++;
            visited[newnode] = true;
            q2.push(newnode);
        }
    }
    
    return cnt2 > cnt1 ? cnt2 - cnt1 : cnt1 - cnt2;
}

int solution(int n, vector<vector<int>> wires) {
    map<int, vector<int>> m;
    for(vector<int> w : wires){
        m[w[0]].push_back(w[1]);
        m[w[1]].push_back(w[0]);
    }
    
    int answer = 99999999;
    for(vector<int> w : wires){
        answer = min(answer, find(w[0], w[1], m, n));
    }
    return answer;
}