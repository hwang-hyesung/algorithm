#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int solution(vector<int> order) {
    int answer = 0, box = 1, num = order.size();
    stack<int> bojo;
    
    for(int i=0;i<num;i++){
        bool flag = false;
        while(box < order[i]){
            bojo.push(box);
            box++;
        }
        
        if(box == order[i]){
            answer++;
            flag = true;
            box++;
            continue;
        } else {
            if(!bojo.empty() && bojo.top()==order[i]){
                answer++;
                bojo.pop();
                flag = true;
            }
        }
        
        if(!flag) return answer;
    }
    return answer;
}