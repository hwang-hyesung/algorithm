#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, m, ret = 1e9, a[51][51], visited[51][51], virus;
int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
vector<pair<int, int>> hos, pick;

int go()
{
    queue<pair<int, int>> q, temp;
    memset(visited, 0, sizeof(visited));
    int cnt = 0, vaccine = 0;
    for (int i = 0; i < m; i++)
    {
        q.push(pick[i]);
    }
    while (!q.empty())
    {
        if (vaccine >= virus)
            return cnt;
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n || a[ny][nx] == 1 || visited[ny][nx] != 0)
                continue;
            if (a[ny][nx] == 0)
            {
                vaccine++;
            }
            visited[ny][nx] = visited[y][x] + 1;
            cnt = max(cnt, visited[ny][nx]);
            q.push(make_pair(ny, nx));
        }
    }
    if (virus > vaccine)
        return 1e9;
    else
        return cnt;
}

void solve(int cur, int cnt)
{
    if (cnt == m)
    {
        ret = min(ret, go());
        return;
    }
    if (cur == hos.size())
        return;

    solve(cur + 1, cnt); // cur 포함안함
    pick.push_back(hos[cur]);
    solve(cur + 1, cnt + 1); // cur 포함
    pick.pop_back();
}
int main()
{

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 2)
            {
                hos.push_back(make_pair(i, j));
            }
            else if (a[i][j] == 0)
            {
                virus++;
            }
        }
    }

    solve(0, 0);
    if (ret == 1e9)
        cout << -1;
    else
        cout << ret;
    return 0;
}
