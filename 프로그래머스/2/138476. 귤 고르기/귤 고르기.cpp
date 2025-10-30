#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    return a.first>=b.first;
}

int solution(int k, vector<int> tangerine) {
    int answer = 0;
    map<int, int> m;
    vector<pair<int, int>> v;
    for(int tan : tangerine){
        m[tan]++;
    }
    
    for(auto p : m){
        v.push_back({p.second, p.first});
    }
    
    sort(v.begin(), v.end(), cmp);
    
    int sum = 0;
    
    for(pair<int, int> p : v){
        sum += p.first;
        answer++;
        if(sum >= k) break;
    }
    return answer;
}