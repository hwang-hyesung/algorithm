#include <vector>
#include <set>
using namespace std;

int solution(vector<int> nums)
{
    int answer=1;
    int n = nums.size()/2;
    set<int> s;
    for(int i : nums){
        s.insert(i);
    }
    if(s.size()>=n) answer = n;
    else answer = s.size();
    return answer;
}