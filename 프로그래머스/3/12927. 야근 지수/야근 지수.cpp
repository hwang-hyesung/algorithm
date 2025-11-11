#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int, vector<int>, less<int>> pq;
    for(int w : works){
        pq.push(w);
    }
    
    while(n-->0){
        if(pq.empty()) break;
        int w = pq.top();
        pq.pop();
        if(w-1<=0) continue;
        pq.push(w-1);
    }
    
    while(!pq.empty()){
        int w = pq.top();
        pq.pop();
        answer += w*w;
    }
    return answer;
}