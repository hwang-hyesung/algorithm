#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    
    queue<pair<int, int>> q;
    q.push({truck_weights[0], 1});
    int bw = truck_weights[0], sec=1, num=1;
   
    while(!q.empty()){
        sec++;
        
        if(sec >= q.front().second+bridge_length){
            bw -= q.front().first;
            q.pop();
        }
        if(num >= truck_weights.size() || bw+truck_weights[num]>weight) continue;
        else {
            q.push({truck_weights[num], sec});
            bw += truck_weights[num];
            num++;
        }
        
    }
    answer = sec;
    return answer;
}