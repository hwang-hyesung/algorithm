#include <string>
#include <vector>

using namespace std;

string makebinary(int b) {
    string res = "";
    while (b > 0) {
        res = char('0' + (b % 2)) + res;
        b /= 2;
    }
    return res.empty() ? "0" : res;
}


vector<int> solution(string s) {
    vector<int> answer(2);
    while(s!="1"){
        int cnt = 0, len = s.length();
        answer[0]++;
        for(int i=0;i<len;i++){
            if(s[i]=='1') cnt++;
        }
        answer[1] += len - cnt;
        s = makebinary(cnt);
    }
    return answer;
}