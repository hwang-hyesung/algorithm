#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b){
    if(a.first==b.first) return a.second < b.second;
    return a.first < b.first;
}

int solution(vector<int> stones, int k) {
    int answer = 0;
    vector<pair<int, int>> stone_sort;
    vector<pair<bool, int>> load;
    load.push_back({true, 1});
    for(int i=0;i<stones.size();i++){
        stone_sort.push_back({stones[i], i+1});
        load.push_back({true, i+2});
    }
    
    sort(stone_sort.begin(), stone_sort.end(), cmp);
    
    for(int i=0;i<stone_sort.size();i++){
        int s = stone_sort[i].second;
        int b = s-1;
        while(true){
            if(load[b].first) break;
            else b--;
        }
        load[b].second =  load[s].second;
        load[s].first = false;
        if(load[b].second-b>k) return stone_sort[i].first;
    }
    
    
    return answer;
}