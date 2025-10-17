#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

int makeorder(vector<int> order, int k, vector<bool> visited, int res, vector<vector<int>> &dungeons){
    int d = res;
    
    if(order.size()==dungeons.size()){
        return res;
    }
    
    for(int i=0;i<dungeons.size();i++){
        if(visited[i] || k < dungeons[i][0]) continue;
        
        k -= dungeons[i][1];
        order.push_back(i);
        visited[i] = true;
        
        d = max(d, makeorder(order, k, visited, res + 1, dungeons));
        
        k += dungeons[i][1];
        order.pop_back();
        visited[i] = false;  
    }
    res = d;
    
    return res;
}

int solution(int k, vector<vector<int>> dungeons) {
    vector<bool> visited(dungeons.size());
    vector<int> road;
    int answer = makeorder(road, k, visited, 0, dungeons);
    return answer;
}