#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int n, m, arr[21][21], w[21][21], ans = 0;
int ts = 1, fs = 2, ls = 3, bs = 6;
int cy = 0, cx = 0, cd = 0;
int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
bool visited[21][21];

void bfs(int y, int x)
{
    queue<pair<int, int>> q;
    vector<pair<int, int>> route;
    q.push({y, x});
    route.push_back({y, x});
    int val = arr[y][x], cnt = 1;
    visited[y][x] = true;
    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx] || arr[ny][nx] != val)
                continue;
            q.push({ny, nx});
            route.push_back({ny, nx});
            visited[ny][nx] = true;
            cnt++;
        }
    }
    for (pair<int, int> p : route)
    {
        w[p.first][p.second] = cnt;
    }
}

void init()
{
    memset(w, 0, sizeof(w));
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j])
            {
                bfs(i, j);
            }
        }
    }
}

void roll(int d)
{
    int nts = ts, nls = ls, nfs = fs;
    if (d == 0) // 0,1
    {
        nts = 7 - ls;
        nls = ts;
    }
    else if (d == 1) // 1,0
    {
        nts = 7 - fs;
        nfs = ts;
    }
    else if (d == 2) // 0,-1
    {
        nts = ls;
        nls = 7 - ts;
    }
    else if (d == 3) // -1,0
    {
        nts = fs;
        nfs = 7 - ts;
    }

    ts = nts;
    fs = nfs;
    ls = nls;
    bs = 7 - ts;

    cy += dy[d];
    cx += dx[d];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }
    init();
    roll(0);
    for (int i = 0; i < m; i++)
    {
        ans += arr[cy][cx] * w[cy][cx];

        if (bs > arr[cy][cx])
        {
            cd = (cd + 1) % 4;
        }
        else if (bs < arr[cy][cx])
        {
            cd = (cd + 3) % 4;
        }

        int ny = cy + dy[cd];
        int nx = cx + dx[cd];
        if (ny < 0 || ny >= n || nx < 0 || nx >= n)
        {
            cd = (cd + 2) % 4;
        }
        roll(cd);
    }
    cout << ans;
    return 0;
}