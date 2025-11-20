#include <string>
#include <cstring>
#include <map>
#include <set>
using namespace std;

int solution(string dirs) {
    int answer = 0;
    
    int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, 1, -1};
    map<char, int> mp = {{'U', 0}, {'D', 1}, {'R', 2}, {'L', 3}};
    
    set<pair<pair<int, int>, pair<int,int>>> s;
    
    int y = 0, x = 0;
    for(int i=0;i<dirs.length();i++){
        int d = mp[dirs[i]];
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny < -5 || ny > 5 || nx < -5 || nx > 5) continue;
        s.insert({{y, x}, {ny, nx}});
        s.insert({{ny, nx}, {y, x}});
        y = ny;
        x = nx;
    }
    answer = s.size()/2;
    return answer;
}