#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<int> arr, int k) {
    vector<int> answer;
    set<int> s;
    int slen = 0;
    
    for(int a : arr){
        if(answer.size() == k) break;
        s.insert(a);
        if(s.size() == slen){
            continue;
        }
        answer.push_back(a);
        slen = s.size();
    }
    
    while(answer.size()<k){
        answer.push_back(-1);
    }
    return answer;
}