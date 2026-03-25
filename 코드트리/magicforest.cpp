#include <bits/stdc++.h>
using namespace std;

int R, C, K;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};
vector<vector<int>> forest;

pair<int, int> move(int idx, int c, int d)
{
    int y = 2, x = c;
    int ry = -1, rx = -1;
    while (y <= R + 3)
    {
        bool goDown = true;
        for (int dir = 1; dir < 4; dir++)
        {
            int ny = y + dy[dir], nx = x + dx[dir];
            if (ny < 0 || ny >= R + 3 || nx < 0 || nx >= C || forest[ny][nx] != 0)
            {
                goDown = false;
                break;
            }
        }

        if (goDown)
        {
            y++;
            continue;
        }

        bool goWest = true;
        for (int dir = 0; dir < 4; dir++)
        {
            if (dir == 1)
                continue;
            int ny = y - 1 + dy[dir], nx = x - 1 + dx[dir];
            if (ny < 0 || ny >= R + 3 || nx < 0 || nx >= C || forest[ny][nx] != 0)
            {
                goWest = false;
                break;
            }
        }

        if (goWest)
        {
            for (int dir = 1; dir < 4; dir++)
            {
                int ny = y + dy[dir], nx = x - 1 + dx[dir];
                if (ny < 0 || ny >= R + 3 || nx < 0 || nx >= C || forest[ny][nx] != 0)
                {
                    goWest = false;
                    break;
                }
            }
        }

        if (goWest)
        {
            y++;
            x--;
            d = (d + 3) % 4;
            continue;
        }

        bool goEast = true;
        for (int dir = 0; dir < 3; dir++)
        {
            int ny = y - 1 + dy[dir], nx = x + 1 + dx[dir];
            if (ny < 0 || ny >= R + 3 || nx < 0 || nx >= C || forest[ny][nx] != 0)
            {
                goEast = false;
                break;
            }
        }

        if (goEast)
        {
            for (int dir = 1; dir < 4; dir++)
            {
                int ny = y + dy[dir], nx = x + 1 + dx[dir];
                if (ny < 0 || ny >= R + 3 || nx < 0 || nx >= C || forest[ny][nx] != 0)
                {
                    goEast = false;
                    break;
                }
            }
        }

        if (goEast)
        {
            y++;
            x++;
            d = (d + 1) % 4;
            continue;
        }

        ry = y - 1;
        rx = x;
        break;
    }

    if (ry < 4)
        return {-1, -1};

    forest[ry][rx] = idx;
    forest[ry - 1][rx] = idx;
    forest[ry + 1][rx] = idx;
    forest[ry][rx - 1] = idx;
    forest[ry][rx + 1] = idx;

    forest[ry + dy[d]][rx + dx[d]] = -1 * idx;
    return {ry, rx};
}

int escape(int y, int x)
{
    int res_row = y;
    vector<vector<bool>> visited(R + 3, vector<bool>(C, false));
    queue<pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = true;

    while (!q.empty())
    {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int dir = 0; dir < 4; dir++)
        {
            int ny = y + dy[dir], nx = x + dx[dir];
            if (ny < 0 || ny >= R + 3 || nx < 0 || nx >= C || visited[ny][nx])
                continue;
            if (forest[ny][nx] == 0)
                continue;
            if (forest[ny][nx] != forest[y][x] && (forest[y][x] > 0 && ((forest[ny][nx] != -1 * forest[y][x]) || forest[ny][nx] > 0)))
                continue;
            q.push({ny, nx});
            visited[ny][nx] = true;
            res_row = max(res_row, ny);
        }
    }
    return res_row - 2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int score = 0;
    cin >> R >> C >> K;
    forest.resize(R + 3, vector<int>(C, 0));
    for (int idx = 1; idx <= K; idx++)
    {
        int c, d;
        cin >> c >> d;
        c--;
        pair<int, int> loc = move(idx, c, d);
        if (loc.first == -1)
        {
            forest.assign(R + 3, vector<int>(C, 0));
            continue;
        }
        score += escape(loc.first, loc.second);
        }
    cout << score;
    return 0;
}