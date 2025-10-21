#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

int n, m, cnt = 0, k, weak = 9999, strong = 1, a[14][14], attack[14][14];
int dy[] = {0, 1, 0, -1, -1, -1, 1, 1};
int dx[] = {1, 0, -1, 0, -1, 1, -1, 1};
int wy, wx, sy, sx;
bool attacked[11][11];
vector<int> visited[11][11];

void find()
{
    weak = 9999;
    strong = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] > 0 && a[i][j] < weak)
                weak = a[i][j];
            if (a[i][j] > strong)
                strong = a[i][j];
        }
    }
    int wflag = false, sflag = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == 0)
                continue;
            if (wflag && weak == a[i][j])
            {
                if (attack[i][j] > attack[wy][wx])
                {
                    wy = i;
                    wx = j;
                }
                else if (attack[i][j] == attack[wy][wx])
                {
                    if (i + j > wy + wx)
                    {
                        wy = i;
                        wx = j;
                    }
                    else if (i + j == wy + wx)
                    {
                        if (j > wx)
                        {
                            wy = i;
                            wx = j;
                        }
                    }
                }
            }
            if (!wflag && weak == a[i][j])
            {
                wx = j;
                wy = i;
                wflag = true;
            }

            if (sflag && strong == a[i][j])
            {
                if (attack[i][j] < attack[sy][sx])
                {
                    sy = i;
                    sx = j;
                }
                else if (attack[i][j] == attack[sy][sx])
                {
                    if (i + j < sy + sx)
                    {
                        sy = i;
                        sx = j;
                    }
                    else if (i + j == sy + sx)
                    {
                        if (j < sx)
                        {
                            sy = i;
                            sx = j;
                        }
                    }
                }
            }
            if (!sflag && strong == a[i][j])
            {
                sy = i;
                sx = j;
                sflag = true;
            }
        }
    }
}

bool bfs()
{
    bool vis[11][11];
    memset(vis, false, sizeof(vis));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            visited[i][j].clear();
        }
    }

    queue<pair<int, int>> q;
    q.push(make_pair(wy, wx));
    vis[wy][wx] = true;
    visited[wy][wx].push_back(wy);
    visited[wy][wx].push_back(wx);

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        // if(y==sy&&x==sx) break;
        for (int i = 0; i < 4; i++)
        {
            int ny = (y + dy[i] + n) % n;
            int nx = (x + dx[i] + m) % m;

            if (a[ny][nx] == 0 || vis[ny][nx])
                continue;

            q.push(make_pair(ny, nx));
            vis[ny][nx] = true;
            visited[ny][nx].push_back(y);
            visited[ny][nx].push_back(x);
        }
    }
    return vis[sy][sx];
}

void laser()
{
    int y = sy, x = sx;
    a[y][x] -= a[wy][wx];
    attacked[y][x] = true;

    while (1)
    {
        int ny = visited[y][x][0];
        int nx = visited[y][x][1];
        if (ny == wy && nx == wx)
            break;
        if (a[ny][nx] > 0)
        {
            a[ny][nx] = max(0, a[ny][nx] - (a[wy][wx] / 2));
            attacked[ny][nx] = true;
            y = ny;
            x = nx;
        }
    }
    attacked[wy][wx] = true;
}

void bomb()
{
    a[sy][sx] -= a[wy][wx];
    attacked[sy][sx] = true;
    for (int i = 0; i < 8; i++)
    {
        int ny = (sy + dy[i] + n) % n;
        int nx = (sx + dx[i] + m) % m;
        if (ny == wy && nx == wx)
            continue;
        if (a[ny][nx] > 0)
        {
            a[ny][nx] = max(0, a[ny][nx] - a[wy][wx] / 2);
            attacked[ny][nx] = true;
        }
    }
    attacked[wy][wx] = true;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }

    fill(&attack[0][0], &attack[0][0] + 121, 0);

    while (cnt < k)
    {
        fill(&attacked[0][0], &attacked[0][0] + 121, false);
        cnt++;
        // 가장 약한, 강한 포탑
        find();
        if (sy == wy && sx == wx)
        {
            break;
        }
        a[wy][wx] += n + m;
        attack[wy][wx] = cnt;
        if (bfs())
        {
            laser();
        }
        else
        {
            bomb();
        }
        // 남은 포탑 ++
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (a[i][j] > 0)
                {
                    if (!attacked[i][j])
                        a[i][j]++;
                }
            }
        }
    }
    strong = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] > strong)
                strong = a[i][j];
        }
    }
    cout << strong;
    return 0;
}