#include <string>
#include <vector>
#include <queue>

using namespace std;


int solution(vector<int> priorities, int location) {
    int answer = 0;
    priority_queue<int> pq;
    queue<pair<int, int>> q;
    int idx = 0;
    for(int pr : priorities){
        pq.push(pr);
        q.push({idx, pr});
        idx++;
    }
    while(!q.empty()){
        int prior = pq.top();
        pair<int, int> job = q.front();
        q.pop();
        if(job.second == prior) {
            pq.pop();
            answer++;
            if(job.first == location){
                return answer;
            }
        }else{
            q.push(job);
        }
    }
    
    return answer;
}