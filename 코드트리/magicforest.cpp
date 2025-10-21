#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

int r, c, k, a[74][74], score = 0;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1}; // 상 우 하 좌, 북동남서;

bool check(int y, int x)
{
    if (y < 0 || x < 0 || y >= r + 3 || x >= c || a[y][x] != 0)
    {
        return false;
    }
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || nx < 0 || ny >= r + 3 || nx >= c || a[ny][nx] != 0)
        {
            return false;
        }
    }
    return true;
}

int bfs(int y, int x)
{
    int visited[74][74];
    int maxcol = y;
    queue<pair<int, int>> q;
    q.push(make_pair(y, x));
    memset(visited, 0, sizeof(visited));
    bool flag = true;
    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        visited[y][x] = 1;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= r + 3 || nx >= c || a[ny][nx] == 0 || visited[ny][nx] != 0)
                continue;
            if (a[y][x] == -1 * a[ny][nx] || a[y][x] == a[ny][nx] || a[y][x] < 0)
            {
                q.push(make_pair(ny, nx));
                visited[ny][nx] = 1;
                maxcol = max(ny, maxcol);
            }
        }
    }
    return maxcol - 2;
}

int main()
{
    cin >> r >> c >> k;
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= k; i++)
    {
        int col, d;
        cin >> col >> d;
        col--;

        int y = 0;
        int x = col;
        while (1)
        { // 숲 경계도 확인해야할듯 -> check 함수
            if (check(y + 1, x))
            { // 남
                y++;
            }
            else if (check(y + 1, x - 1) && check(y, x - 1))
            { // 서남
                d = (d + 3) % 4;
                y++;
                x--;
            }
            else if (check(y + 1, x + 1) && check(y, x + 1))
            { // 동남
                d = (d + 1) % 4;
                y++;
                x++;
            }
            else
            {
                break;
            }
        }

        if (y > 3)
        {
            a[y][x] = i;
            for (int z = 0; z < 4; z++)
            {
                if (d == z)
                    a[y + dy[z]][x + dx[z]] = -i;
                else
                    a[y + dy[z]][x + dx[z]] = i;
            }
            score += bfs(y, x);
            // cout << score << "\n";
            // for(int z=2;z<r+3;z++){
            //     for(int x=0;x<c;x++){
            //         cout << a[z][x] << " ";
            //     }
            //     cout << "\n";
            // }
            // cout << "\n";
        }
        else
        {
            memset(a, 0, sizeof(a));
        }
    }
    cout << score;
    return 0;
}
