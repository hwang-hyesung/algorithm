#include <string>
#include <vector>
#include <stack>

using namespace std;

bool check(string s){
    stack<char> stk;
    int i=0;
    while(i<s.length()){
        if(s[i]=='(') stk.push('(');
        else if(!stk.empty()){
            stk.pop();
        }else return false;
        i++;
    }
    if(stk.empty()) return true;
    else return false;
}

int find(string s, int l, int r, int n){
    int cnt = 0;
    if(s.length()==n) {
        return 1;
        // if(check(s)) return 1;
        // else return 0;
    }
    if(l>r) cnt += find(s+")", l, r+1, n);
    if(l<n/2) cnt += find(s+"(", l+1, r, n);
    return cnt;
}

int solution(int n) {
    int answer = find("(",1,0,2*n);
    return answer;
}