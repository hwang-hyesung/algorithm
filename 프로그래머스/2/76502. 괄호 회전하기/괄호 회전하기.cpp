#include <string>
#include <vector>
#include <stack>

using namespace std;
bool check(int start, string str){
    stack<char> stk;
    for(int i=0;i<str.length();i++){
        int idx = (i+start)%str.length();
        if(str[idx] == '['){
            stk.push(']');
        }else if(str[idx] == '{'){
            stk.push('}');
        }else if(str[idx] == '('){
            stk.push(')');
        }else {
            if(str[idx]==stk.top()) stk.pop();
            else return false;
        }
    }
    if(!stk.empty()) return false;
    return true;
}

int solution(string s) {
    int answer = 0;
    for(int i=0;i<s.length();i++){
        if(check(i,s)) answer++;
    }
    return answer;
}