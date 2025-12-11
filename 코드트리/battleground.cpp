#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

struct Player
{
    int x, y, d, s;
    int p = 0, gun = 0;
};
int n, m, k, dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};
priority_queue<int> arr[20][20];
int loc[20][20];
vector<Player> players;

void win(int idx, int opidx, int y, int x)
{
    if (players[opidx].gun > 0)
        arr[y][x].push(players[opidx].gun);
    players[opidx].gun = 0;
    int d = players[opidx].d;

    loc[players[idx].y][players[idx].x] = 0;

    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[(d + i) % 4];
        int nx = x + dx[(d + i) % 4];

        if (ny < 0 || ny >= n || nx < 0 || nx >= n || loc[ny][nx] != 0)
        {
            continue;
        }
        players[opidx].y = ny;
        players[opidx].x = nx;
        loc[ny][nx] = opidx;
        players[opidx].d = (d + i) % 4;
        if (!arr[ny][nx].empty())
        {
            int ng = arr[ny][nx].top();
            if (ng > players[opidx].gun)
            {
                arr[ny][nx].pop();
                if (players[opidx].gun > 0)
                    arr[ny][nx].push(players[opidx].gun);
                players[opidx].gun = ng;
            }
        }
        break;
    }

    loc[y][x] = idx;
    players[idx].y = y;
    players[idx].x = x;

    if (!arr[y][x].empty())
    {
        int ng = arr[y][x].top();
        if (ng <= players[idx].gun)
            return;
        arr[y][x].pop();
        if (players[idx].gun > 0)
            arr[y][x].push(players[idx].gun);
        players[idx].gun = ng;
    }
}

void lose(int idx, int opidx, int y, int x)
{
    arr[y][x].push(players[idx].gun);
    players[idx].gun = 0;
    int d = players[idx].d;
    loc[players[idx].y][players[idx].x] = 0;

    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[(d + i) % 4];
        int nx = x + dx[(d + i) % 4];

        if (ny < 0 || ny >= n || nx < 0 || nx >= n || loc[ny][nx] != 0)
        {
            continue;
        }
        players[idx].y = ny;
        players[idx].x = nx;
        loc[ny][nx] = idx;
        players[idx].d = (d + i) % 4;
        if (!arr[ny][nx].empty())
        {
            int ng = arr[ny][nx].top();
            if (ng > players[idx].gun)
            {
                arr[ny][nx].pop();
                if (players[idx].gun > 0)
                    arr[ny][nx].push(players[idx].gun);
                players[idx].gun = ng;
            }
        }
        break;
    }

    int ng = arr[y][x].top();
    if (ng <= players[opidx].gun)
        return;
    arr[y][x].pop();
    if (players[opidx].gun > 0)
        arr[y][x].push(players[opidx].gun);
    players[opidx].gun = ng;
}

void move(int idx)
{

    int y = players[idx].y;
    int x = players[idx].x;
    int d = players[idx].d;

    int ny = y + dy[d];
    int nx = x + dx[d];
    if (ny < 0 || ny >= n || nx < 0 || nx >= n)
    {
        ny = y - dy[d];
        nx = x - dx[d];
        players[idx].d = (players[idx].d + 2) % 4;
    }

    if (loc[ny][nx] == 0)
    {
        players[idx].y = ny;
        players[idx].x = nx;
        loc[y][x] = 0;
        loc[ny][nx] = idx;
        if (!arr[ny][nx].empty())
        {
            int ng = arr[ny][nx].top();
            if (ng <= players[idx].gun)
                return;
            arr[ny][nx].pop();

            if (players[idx].gun > 0)
                arr[ny][nx].push(players[idx].gun);
            players[idx].gun = ng;
        }
    }
    else
    {
        int opidx = loc[ny][nx];
        int myscore = players[idx].s + players[idx].gun;
        int opscore = players[opidx].s + players[opidx].gun;
        if (myscore > opscore)
        {
            players[idx].p += (myscore - opscore);
            win(idx, opidx, ny, nx);
        }
        else if (myscore < opscore)
        {
            players[opidx].p += (opscore - myscore);
            lose(idx, opidx, ny, nx);
        }
        else
        {
            if (players[idx].s > players[opidx].s)
            {
                win(idx, opidx, ny, nx);
            }
            else
            {
                lose(idx, opidx, ny, nx);
            }
        }
    }
}

int main()
{
    cin >> n >> m >> k;

    players.resize(m + 1);
    memset(loc, 0, sizeof(loc));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int p;
            cin >> p;
            if (p > 0)
                arr[i][j].push(p);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> players[i].y >> players[i].x >> players[i].d >> players[i].s;
        players[i].x--;
        players[i].y--;
        loc[players[i].y][players[i].x] = i;
    }

    while (k-- > 0)
    {
        for (int i = 1; i <= m; i++)
        {
            move(i);
        }
    }

    for (int i = 1; i <= m; i++)
    {
        cout << players[i].p << " ";
    }
}
