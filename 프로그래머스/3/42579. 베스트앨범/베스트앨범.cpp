#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    if(a.second == b.second) return a.first< b.first;
    return a.second > b.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    map<string, vector<pair<int, int>>> m;
    map<string, int> total;
    
    for(int i=0;i<genres.size();i++){
        m[genres[i]].push_back({i, plays[i]});
        total[genres[i]] += plays[i];
    }
    
    vector<pair<string, int>> genreOrder(total.begin(), total.end());
    sort(genreOrder.begin(), genreOrder.end(), [](auto &a, auto &b) { return a.second > b.second; });

        
    for (auto &g : genreOrder) {
        auto &songs = m[g.first];
        sort(songs.begin(), songs.end(), cmp);
        int len = min(2, (int)songs.size());
        for (int i = 0; i < len; i++) {
            answer.push_back(songs[i].first);
        }
    }
    
    
    return answer;
}