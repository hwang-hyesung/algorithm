#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

vector<int> solution(vector<string> gems) {
    set<string> gtypes(gems.begin(), gems.end());
    int total = gtypes.size();
    
    unordered_map<string, int> cnt;
    
    int left = 0;
    int right = 0;
    int n = gems.size();
    
    int minLen = 1e9;
    vector<int> answer(2);
    
    while(true){
        if(cnt.size() == total){
            if(right - left < minLen){
                minLen = right - left;
                answer = {left+1, right};
            }
            
            cnt[gems[left]]--;
            if(cnt[gems[left]] == 0)
                cnt.erase(gems[left]);
            left++;
        }
        else{
            if(right == n) break;
            cnt[gems[right]]++;
            right++;
        }
    }
    
    return answer;
}