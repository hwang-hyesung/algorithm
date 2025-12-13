#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m, k, arr[21][21], load[21][21], rnd = 0, dy[] = {0, -1, 0, 1}, dx[] = {1, 0, -1, 0}, sum = 0;
bool visited[21][21];
vector<vector<pair<int, int>>> team;

void dfs(int idx, int y, int x)
{
    visited[y][x] = true;
    load[y][x] = idx;
    if (arr[y][x] != 4)
        team[idx].push_back({y, x});
    for (int d = 0; d < 4; d++)
    {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (ny < 0 || ny >= n || nx < 0 || nx >= n || arr[ny][nx] == 0)
            continue;
        if ((arr[y][x] == 1 && arr[ny][nx] == 2) || (arr[y][x] != 1 && !visited[ny][nx]))
        {
            dfs(idx, ny, nx);
        }
    }
}

void init()
{
    int idx = 1;
    memset(load, 0, sizeof(load));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == 1)
            {
                dfs(idx++, i, j);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == 2 || arr[i][j] == 3)
            {
                arr[i][j] = 1;
            }
        }
    }
}

void move()
{
    for (int i = 1; i <= m; i++)
    {
        vector<pair<int, int>> &b = team[i];
        pair<int, int> head = b[0];
        pair<int, int> noHead = b[1];
        pair<int, int> newHead;

        pair<int, int> oldTail = b.back();
        arr[oldTail.first][oldTail.second] = 4;
        b.pop_back();

        for (int d = 0; d < 4; d++)
        {
            int ny = head.first + dy[d];
            int nx = head.second + dx[d];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n || make_pair(ny, nx) == noHead)
                continue;

            if (arr[ny][nx] == 4)
            {
                newHead = {ny, nx};
                break;
            }
        }

        b.insert(b.begin(), newHead);
        arr[newHead.first][newHead.second] = 1;
    }
}

void throwBall(int round)
{
    round %= (4 * n);
    int sy, sx, dir;
    if (round < n)
    {
        sy = round;
        sx = 0;
        dir = 0;
    }
    else if (round < 2 * n)
    {
        sy = n - 1;
        sx = round - n;
        dir = 1;
    }
    else if (round < 3 * n)
    {
        int t = round - 2 * n;
        sy = n - 1 - t;
        sx = n - 1;
        dir = 2;
    }
    else
    {
        int t = round - 3 * n;
        sy = 0;
        sx = n - 1 - t;
        dir = 3;
    }

    while (true)
    {
        if (arr[sy][sx] == 1)
        {
            int tidx = load[sy][sx];
            auto it = find(team[tidx].begin(), team[tidx].end(), make_pair(sy, sx));
            if (it != team[tidx].end())
            {
                int th = 1 + distance(team[tidx].begin(), it);
                sum += th * th;
                reverse(team[tidx].begin(), team[tidx].end());
                break;
            }
        }

        sy += dy[dir];
        sx += dx[dir];
        if (sy < 0 || sy >= n || sx < 0 || sx >= n)
            break;
    }
}

int main()
{
    cin >> n >> m >> k;
    team.resize(m + 1);
    memset(visited, false, sizeof(visited));
    memset(load, 0, sizeof(load));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    init();
    memset(visited, false, sizeof(visited));

    for (rnd = 0; rnd < k; rnd++)
    {
        move();
        throwBall(rnd);
    }

    cout << sum;
    return 0;
}
