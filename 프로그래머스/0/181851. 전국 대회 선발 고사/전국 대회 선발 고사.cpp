#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> rank, vector<bool> attendance) {
    int answer = 0;
    int order = 10000;
    vector<pair<int, int>> ranking;
    
    for(int i=0;i<rank.size();i++){
        if(!attendance[i]) continue;
        ranking.push_back({rank[i], i});
    }
    
    sort(ranking.begin(), ranking.end());
    
    for(int i=0;i<3;i++){
        answer += ranking[i].second*order;
        order/=100;
    }
    return answer;
}