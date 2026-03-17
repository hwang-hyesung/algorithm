#include <bits/stdc++.h>
using namespace std;

int n, m, f, sy = -1, sx = -1, my = -1, mx = -1, dy[] = {0, 0, 1, -1}, dx[] = {1, -1, 0, 0};
vector<vector<int>> space_grid;
vector<vector<int>> svisited;
vector<vector<vector<int>>> views;
vector<vector<vector<int>>> vvisited;
vector<vector<int>> anomalies;

const int EAST = 0;
const int WEST = 1;
const int SOUTH = 2;
const int NORTH = 3;
const int TOP = 4;
const int BOTTOM = 5;

void init()
{
    cin >> n >> m >> f;

    space_grid.resize(n, vector<int>(n));
    anomalies.resize(n, vector<int>(n, -1));
    svisited.resize(n, vector<int>(n, -1));
    views.resize(5, vector<vector<int>>(m, vector<int>(m)));
    vvisited.resize(5, vector<vector<int>>(m, vector<int>(m, -1)));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> space_grid[i][j];
            if (my == -1 && space_grid[i][j] == 3)
            {
                my = i;
                mx = j;
            }
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < m; k++)
            {
                cin >> views[i][j][k];
                if (i == TOP && views[i][j][k] == 2)
                {
                    sy = j;
                    sx = k;
                }
            }
        }
    }

    for (int i = 0; i < f; i++)
    {
        int r, c, d, v;
        cin >> r >> c >> d >> v;
        int cnt = 1;
        anomalies[r][c] = 0;
        while (true)
        {
            r += dy[d];
            c += dx[d];
            if (r < 0 || r >= n || c < 0 || c >= n || space_grid[r][c] != 0)
                break;
            anomalies[r][c] = v * cnt++;
        }
    }
}

vector<int> nextPoint(vector<int> p, int d)
{
    int side = p[0];
    int y = p[1];
    int x = p[2];

    int ny = y + dy[d], nx = x + dx[d];
    if (0 <= ny && ny < m && 0 <= nx && nx < m)
        return {side, ny, nx};

    switch (side)
    {
    case EAST:
        if (ny < 0)
            return {TOP, m - 1 - x, m - 1};
        if (ny >= m)
            return {BOTTOM, my + (m - 1 - x), mx + m};
        if (nx < 0)
            return {SOUTH, y, m - 1};
        if (nx >= m)
            return {NORTH, y, 0};
        break;

    case WEST:
        if (ny < 0)
            return {TOP, x, y};
        if (ny >= m)
            return {BOTTOM, my + x, mx - 1};
        if (nx < 0)
            return {NORTH, m - 1, y};
        if (nx >= m)
            return {SOUTH, y, 0};
        break;

    case SOUTH:
        if (ny < 0)
            return {TOP, m - 1, x};
        if (ny >= m)
            return {BOTTOM, my + m, mx + x};
        if (nx < 0)
            return {WEST, y, m - 1};
        if (nx >= m)
            return {EAST, y, 0};
        break;

    case NORTH:
        if (ny < 0)
            return {TOP, 0, m - 1 - x};
        if (ny >= m)
            return {BOTTOM, my - 1, mx + (m - 1 - x)};
        if (nx < 0)
            return {EAST, y, m - 1};
        if (nx >= m)
            return {WEST, y, 0};
        break;

    case TOP:
        if (ny < 0)
            return {NORTH, 0, m - 1 - x};
        if (ny >= m)
            return {SOUTH, 0, x};
        if (nx < 0)
            return {WEST, x, y};
        if (nx >= m)
            return {EAST, 0, m - 1 - y};
        break;
    }

    return {-1, -1, -1};
}

void findExit()
{
    queue<vector<int>> q;
    q.push({TOP, sy, sx});
    vvisited[TOP][sy][sx] = 0;

    int ey = -1, ex = -1;
    while (!q.empty())
    {
        vector<int> p = q.front();
        q.pop();

        bool flag = true;
        for (int i = 0; i < 4; i++)
        {
            vector<int> np = nextPoint(p, i);

            if (np[0] == BOTTOM)
            {

                if (space_grid[np[1]][np[2]] == 0)
                {
                    if (anomalies[np[1]][np[2]] != -1 && anomalies[np[1]][np[2]] <= vvisited[p[0]][p[1]][p[2]] + 1)
                    {
                        flag = false;
                        break;
                    }
                    svisited[np[1]][np[2]] = vvisited[p[0]][p[1]][p[2]] + 1;
                    ey = np[1];
                    ex = np[2];
                    flag = false;
                    break;
                }
                else
                    continue;
            }
            if (views[np[0]][np[1]][np[2]] != 0 || vvisited[np[0]][np[1]][np[2]] != -1)
                continue;
            q.push(np);
            vvisited[np[0]][np[1]][np[2]] = vvisited[p[0]][p[1]][p[2]] + 1;
        }
        if (!flag)
            break;
    }

    if (ey == -1)
    {
        cout << ey;
        return;
    }

    queue<pair<int, int>> qq;
    qq.push({ey, ex});

    while (!qq.empty())
    {
        int y = qq.front().first;
        int x = qq.front().second;
        qq.pop();

        if (space_grid[y][x] == 4)
        {
            cout << svisited[y][x];
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n || space_grid[ny][nx] == 1)
                continue;
            if (svisited[ny][nx] != -1 || (anomalies[ny][nx] != -1 && anomalies[ny][nx] <= svisited[y][x] + 1))
                continue;
            qq.push({ny, nx});
            svisited[ny][nx] = svisited[y][x] + 1;
        }
    }
    cout << -1;
    return;
}

int main()
{
    init();

    findExit();

    return 0;
}