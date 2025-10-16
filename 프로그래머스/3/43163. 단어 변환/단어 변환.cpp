#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    if(find(words.begin(), words.end(), target) == words.end()) return answer;
    words.insert(words.begin(), begin);
    map<string, vector<pair<int, string>>> m;
    int len = words[0].length();
    for(int i=0;i<words.size();i++){
        for(int j=0;j<words.size();j++){
            int cnt = 0;
            for(int k=0;k<len;k++){
                if(words[i][k] != words[j][k]){
                    cnt++;
                    if(cnt>1) break;
                }
            }
            if(cnt==1) m[words[i]].push_back({j,words[j]});
        }
    }
    
    int arr[51];
    memset(arr, -1, sizeof(arr));
    queue<pair<int, string>> q;
    q.push({0, begin});
    arr[0] = 0;
    while(!q.empty()){
        int idx = q.front().first;
        string word = q.front().second;
        q.pop();
        
        for(pair<int, string> p : m[word]){
            if(p.second == target) return arr[idx]+1;
            if(arr[p.first]!=-1) continue;
            q.push(p);
            arr[p.first] = arr[idx]+1;
        }
    }
    
    return answer;
}