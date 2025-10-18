#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(const vector<int> &a, const vector<int> &b){
    return a[1] < b[1];
}

int solution(vector<vector<int>> routes) {
    sort(routes.begin(), routes.end(), cmp);
    int answer = 1;
    int p = routes[0][1];
    for(vector<int> r : routes){
        if(p<r[0]){
            p=r[1];
            answer++;
        }
    }
    return answer;
}