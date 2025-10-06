#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;
    int w, h;
    
    for(int i=1;i<=yellow;i++){
        if(yellow%i==0){
            w=max(i+2, yellow/i+2);
            h=min(i+2, yellow/i+2);
            if(2*(w+h)-4==brown) {
                answer.push_back(w);
                answer.push_back(h);
                break;
            }
        }else continue;
    }
    return answer;
}