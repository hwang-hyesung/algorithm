#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int s : scoville){
        pq.push(s);
    }
    while(true){
        int f = pq.top();
        if(f>=K) break;
        if(pq.size()<2) {
            answer =-1;
            break;
        }
        pq.pop();
        int s = pq.top();
        pq.pop();
        
        int n = f+ 2*s;
        if(n<K && pq.empty()) {
            answer =-1;
            break;
        }
        pq.push(n);
        answer++;
        
    }
    return answer;
}