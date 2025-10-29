#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> seoul) {
    string answer = "김서방은 ";
    // for(int i=0;i<seoul.size();i++){
    //     if(seoul[i]=="Kim") {
    //         answer += to_string(i);
    //         break;
    //     }
    // }
    answer += to_string(distance(seoul.begin(), find(seoul.begin(), seoul.end(), "Kim")));
    answer += "에 있다";
    return answer;
}