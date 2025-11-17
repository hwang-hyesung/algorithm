#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int n, k, l, total = 0;
vector<vector<int>> room(30, vector<int>(30, 0));
vector<vector<int>> rloc(30, vector<int>(30, 0));
vector<pair<int, int>> robot;
int dy[] = {-1, 0, 1, 0}, dx[] = {0, -1, 0, 1};
int mdy[] = {0, -1, 0, 1, 0}, mdx[] = {-1, 0, 1, 0, 0};

void move(int idx)
{
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    int sy = robot[idx].first, sx = robot[idx].second;
    visited[sy][sx] = true;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
    q.push({0, {sy, sx}});

    int ty = sy, tx = sx, td = 0;

    while (!q.empty())
    {
        int d = q.top().first;
        int y = q.top().second.first;
        int x = q.top().second.second;
        q.pop();

        if (room[y][x] > 0)
        {
            ty = y;
            tx = x;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n ||
                visited[ny][nx] || room[ny][nx] < 0 || rloc[ny][nx] != 0)
                continue;
            visited[ny][nx] = true;
            q.push({d + 1, {ny, nx}});
        }
    }

    rloc[sy][sx] = 0;
    robot[idx] = {ty, tx};
    rloc[ty][tx] = idx + 1;
}

int findDir(int idx)
{
    int y = robot[idx].first, x = robot[idx].second;
    int mdir = -1, md = -1;

    for (int no = 0; no < 4; no++)
    {
        int s = 0;
        for (int k = 0; k < 5; k++)
        {
            int ny = y + mdy[k], nx = x + mdx[k];
            if (ny < 0 || ny >= n || nx < 0 || nx >= n)
                continue;
            if (k < 4 && k == no)
                continue;
            if (room[ny][nx] > 0)
                s += min(20, room[ny][nx]);
        }
        if (s > md)
        {
            md = s;
            mdir = no;
        }
    }
    return mdir;
}

void clean(int idx)
{
    int dir = findDir(idx);
    int y = robot[idx].first, x = robot[idx].second;
    int dust = 0;

    for (int i = 0; i < 5; i++)
    {
        if (i == dir)
            continue;
        int ny = y + mdy[i], nx = x + mdx[i];
        if (ny < 0 || ny >= n || nx < 0 || nx >= n || room[ny][nx] <= 0)
            continue;
        dust += (room[ny][nx] > 20 ? 20 : room[ny][nx]);
        room[ny][nx] = (room[ny][nx] > 20 ? room[ny][nx] - 20 : 0);
    }

    total -= dust;
}

void addDust()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (room[i][j] > 0)
            {
                total += 5;
                room[i][j] += 5;
            }
        }
    }
}

void spreadDust()
{
    vector<vector<bool>> visited(30, vector<bool>(30, true));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (room[i][j] == 0)
            {
                int dust = 0;
                for (int d = 0; d < 4; d++)
                {
                    int ny = i + dy[d], nx = j + dx[d];
                    if (ny < 0 || ny >= n || nx < 0 || nx >= n || room[ny][nx] <= 0 || !visited[ny][nx])
                        continue;
                    dust += room[ny][nx];
                }
                dust /= 10;
                room[i][j] += dust;
                total += dust;
                visited[i][j] = false;
            }
        }
    }
}

int main()
{

    cin >> n >> k >> l;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> room[i][j];
            if (room[i][j] > 0)
                total += room[i][j];
        }
    }

    for (int i = 0; i < k; i++)
    {
        int y, x;
        cin >> y >> x;
        y--;
        x--;
        robot.push_back({y, x});
        rloc[y][x] = i + 1;
    }

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < k; j++)
        {
            move(j);
        }

        for (int j = 0; j < k; j++)
        {
            clean(j);
        }

        addDust();

        spreadDust();

        // cout << '\n';
        // for (int r = 0; r < n; r++)
        // {
        //     for (int c = 0; c < n; c++)
        //     {
        //         cout << room[r][c] << "\t";
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';

        cout << total << "\n";
    }
    return 0;
}