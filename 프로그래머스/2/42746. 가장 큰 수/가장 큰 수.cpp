#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const int& a, const int& b){
    string astr = to_string(a);
    string bstr = to_string(b);
    
    return astr+bstr > bstr+astr;
}

string solution(vector<int> numbers) {
    string answer = "";
    
    sort(numbers.begin(), numbers.end(), cmp);
    
    for(int n : numbers){
        answer += to_string(n);
    }
    return answer[0] == '0' ? "0" : answer;
}