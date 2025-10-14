#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <tuple>

using namespace std;

int solution(vector<int> arrows) {
    int answer = 0;
    int dy[]={-1, -1, 0, 1, 1, 1, 0, -1}, dx[]={0, 1, 1, 1, 0, -1, -1, -1};
    set<pair<int,int>> nodes;
    set<tuple<int,int,int,int>> edges;
    int y = 0, x = 0;
    nodes.insert({0,0});
    for(int a : arrows){
        for(int i=0;i<2;i++){
            int ny = y + dy[a];
            int nx = x + dx[a];

            if (nodes.count({ny, nx}) && !edges.count({y, x, ny, nx})) {
                answer++;
            }

            nodes.insert({ny, nx});
            edges.insert({y, x, ny, nx});
            edges.insert({ny, nx, y, x});

            y = ny;
            x = nx;
        }
        
    }
    
    return answer;
}