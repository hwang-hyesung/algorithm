#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer;
    stack<int> stk;
    for(int a : arr){
        if(stk.empty() || stk.top() != a){
            stk.push(a);
        }else if (stk.top() == a){
            stk.pop();
        }
    }
    
    if(stk.empty()) {
        answer.push_back(-1);
        return answer;
    }
    
    while(!stk.empty()){
        int n = stk.top();
        stk.pop();
        answer.insert(answer.begin(), n);
    }
    return answer;
}