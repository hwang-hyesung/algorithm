#include <string>
#include <vector>

using namespace std;

string solution(int age) {
    string answer = "";
    string agestr = to_string(age);
    for(char a: agestr){
        answer += 'a' + a - '0';
    }
    return answer;
}