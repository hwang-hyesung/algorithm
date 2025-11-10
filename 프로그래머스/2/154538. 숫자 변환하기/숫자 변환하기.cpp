#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int x, int y, int n) {
    if (x==y) return 0;
    int answer = 0;
    vector<int> v(y+1, 0);
    queue<pair<int, int>> q;
    q.push({x, 0});
    while(!q.empty()){
        int num = q.front().first;
        int cnt = q.front().second;
        q.pop();
        
        if(num+n<=y && v[num+n]==0) {
            v[num+n] = cnt+1;
            q.push({num+n, cnt+1});
        }
        
        if(num*2<=y && v[num*2]==0) {
            v[num*2] = cnt+1;
            q.push({num*2, cnt+1});
        }
        
        if(num*3<=y && v[num*3]==0) {
            v[num*3] = cnt+1;
            q.push({num*3, cnt+1});
        } 
    }
    return v[y]==0?-1:v[y];
}