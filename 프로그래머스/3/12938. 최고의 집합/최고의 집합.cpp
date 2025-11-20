#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    if(s<n) return {-1};
    
    for(int i=0;i<n;i++){
        if(n-i<=(s%n)){
            answer.push_back(s/n+1);
        }else{
            answer.push_back(s/n);
        }
    }
    return answer;
}