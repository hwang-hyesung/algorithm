#include <string>
#include <vector>
#include <stack>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    vector<char> stk;
    
    for(char c : number) {
        while(!stk.empty() && k > 0 && stk.back() < c) {
            stk.pop_back();
            k--;
        }
        stk.push_back(c);
    }
    
    while(k > 0) {
        stk.pop_back();
        k--;
    }
    
    for(char c : stk) answer += c;
    
    return answer;
}
