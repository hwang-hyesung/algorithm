#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int N, M, K, T, arr[21][21], cold[21][21];
int dy[] = {0, -1, 0, 1}, dx[] = {-1, 0, 1, 0};
bool wall[21][21][4];

bool inrange(int y, int x)
{
    return y >= 0 && y < N && x >= 0 && x < N;
}

void blow(int y, int x, int dir)
{
    bool visited[21][21];
    memset(visited, false, sizeof(visited));

    vector<vector<int>> bdir;
    if (dir % 2 == 0)
    {
        bdir.push_back({1, dir});
        bdir.push_back({dir});
        bdir.push_back({3, dir});
    }
    else
    {
        bdir.push_back({0, dir});
        bdir.push_back({dir});
        bdir.push_back({2, dir});
    }
    queue<vector<int>> q;
    q.push({y + dy[dir], x + dx[dir], 5});
    visited[y + dy[dir]][x + dx[dir]] = true;
    cold[y + dy[dir]][x + dx[dir]] += 5;
    while (!q.empty())
    {
        int y = q.front()[0];
        int x = q.front()[1];
        int v = q.front()[2];
        q.pop();

        if (v == 1)
            continue;

        for (vector<int> bd : bdir)
        {
            int ny = y, nx = x;
            bool canblow = true;
            for (int wd : bd)
            {
                if (!wall[ny][nx][wd])
                {
                    canblow = false;
                    break;
                }
                ny += dy[wd];
                nx += dx[wd];
                if (!inrange(ny, nx) || visited[ny][nx])
                {
                    canblow = false;
                    break;
                }
            }
            if (canblow)
            {
                visited[ny][nx] = true;
                q.push({ny, nx, v - 1});
                cold[ny][nx] += v - 1;
            }
        }
    }
}

void mix()
{
    int temp[N][N];
    memset(temp, 0, sizeof(temp));

    for (int y = 0; y < N; y++)
    {
        for (int x = 0; x < N; x++)
        {
            int val = cold[y][x];
            for (int d = 0; d < 4; d++)
            {
                if (!wall[y][x][d])
                    continue;
                int ny = y + dy[d];
                int nx = x + dx[d];
                if (!inrange(ny, nx))
                    continue;
                if ((val - cold[ny][nx]) / 4 > 0)
                {
                    temp[y][x] -= (val - cold[ny][nx]) / 4;
                    temp[ny][nx] += (val - cold[ny][nx]) / 4;
                }
            }
        }
    }
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            cold[y][x] += temp[y][x];
}

void heat()
{
    for (int i = 0; i < N - 1; i++)
    {
        if (cold[0][i] > 0)
            cold[0][i]--;
        if (cold[N - 1][i + 1] > 0)
            cold[N - 1][i + 1]--;
        if (cold[i][N - 1] > 0)
            cold[i][N - 1]--;
        if (cold[i + 1][0] > 0)
            cold[i + 1][0]--;
    }
}

bool check()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (arr[i][j] == 1 && cold[i][j] < K)
                return false;
    return true;
}

int main()
{
    memset(cold, 0, sizeof(cold));
    memset(wall, true, sizeof(wall));

    cin >> N >> M >> K;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> arr[i][j];

    for (int i = 0; i < M; i++)
    {
        int y, x, w;
        cin >> y >> x >> w;
        if (w == 0)
        {
            wall[y - 1][x - 1][1] = false;
            wall[y - 2][x - 1][3] = false;
        }
        else
        {
            wall[y - 1][x - 1][0] = false;
            wall[y - 1][x - 2][2] = false;
        }
    }

    while (!check())
    {
        if (T > 100)
            break;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (arr[i][j] > 1)
                    blow(i, j, arr[i][j] - 2);

        mix();
        heat();
        T++;
    }
    if (T > 100)
        T = -1;
    cout << T;
    return 0;
}