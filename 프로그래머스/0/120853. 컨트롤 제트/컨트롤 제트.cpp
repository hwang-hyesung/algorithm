#include <string>
#include <sstream>
#include <stack>

using namespace std;

int solution(string s) {
    int answer = 0;
    stack<int> his;
    stringstream ss(s); 
    string word;

    while (getline(ss, word, ' ')) {
        
        if(word=="Z") his.pop();
        else if(his.empty()) {
            int num = stoi(word);
            his.push(num);
        }else {
            int num = stoi(word);
            his.push(his.top()+num);
        }
    }
    answer = his.top();
    return answer;
}