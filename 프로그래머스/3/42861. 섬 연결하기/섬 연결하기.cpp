#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> connected;

int getParent(int node){
    if(connected[node]==node){
        return node;
    }
    
    return getParent(connected[node]);
}

bool cmp(const vector<int> &a, const vector<int> &b){
    return a[2] <= b[2];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    connected.resize(n);
    for(int i=0;i<n;i++){
        connected[i] = i;
    }
    
    sort(costs.begin(), costs.end(), cmp);
    
    for(vector<int> c : costs){
        int f = getParent(c[0]);
        int s = getParent(c[1]);
        
        if(f!=s) {
            connected[s] = f;
            answer += c[2];
        }
        
    }
    return answer;
}