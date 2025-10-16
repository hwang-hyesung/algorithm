#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
    int answer = 0;
    int arr[102][102], visited[102][102];
    int dy[]={-1, 1, 0, 0}, dx[]={0, 0, -1, 1};
    memset(arr, 0, sizeof(arr));
    memset(visited, -1, sizeof(visited));
    
    for (auto &r : rectangle) {
        int x1 = r[0]*2, y1 = r[1]*2, x2 = r[2]*2, y2 = r[3]*2;
        for (int y = y1; y <= y2; y++) {
            for (int x = x1; x <= x2; x++) {
                if (y==y1 || y==y2 || x==x1 || x==x2) {
                    if (arr[y][x] != 2)
                        arr[y][x] = 1;
                } else arr[y][x] = 2;
            }
        }
    }
    
    queue<pair<int, int>> q;
    q.push({characterY*2, characterX*2});
    visited[characterY*2][characterX*2] = 0;
    while(!q.empty()){
        int y = q.front().first, x = q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int ny = y + dy[i], nx = x + dx[i];
            if(ny < 0 || ny >= 102 || nx < 0 || nx >= 102
               || arr[ny][nx] != 1 || visited[ny][nx] != -1) 
                continue;
            q.push({ny, nx});
            visited[ny][nx] = visited[y][x]+1;
            if(ny == itemY*2 && nx == itemX*2) {
                answer = visited[ny][nx]/2;
            }
        }
        if(answer!=0) break;
    }
    
    return answer;
}