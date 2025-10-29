#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string solution(string s) {
    string answer = "";
    bool upper = true;
    for(int i=0;i<s.length();i++){
        if(s[i]==' ') {
            answer += " ";
            upper = true;
        }
        else if(upper && (s[i]>='a'&&s[i]<='z')) {
            answer += s[i]-'a'+'A';
            upper = false;
        }
        else if(!upper && (s[i]>='A'&&s[i]<='Z')) {
            answer += s[i]-'A'+'a';
        }else {
            answer += s[i];
            upper = false;
        }
        
    }
    return answer;
}